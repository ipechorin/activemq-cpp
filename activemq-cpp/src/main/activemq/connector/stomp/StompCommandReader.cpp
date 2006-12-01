/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "StompCommandReader.h"

#include <activemq/connector/stomp/commands/CommandConstants.h>
#include <activemq/concurrent/Thread.h>
#include <activemq/util/Character.h>

using namespace std;
using namespace activemq;
using namespace activemq::concurrent;
using namespace activemq::connector;
using namespace activemq::connector::stomp;
using namespace activemq::transport;
using namespace activemq::io;
using namespace activemq::exceptions;
using namespace activemq::util;

////////////////////////////////////////////////////////////////////////////////
StompCommandReader::StompCommandReader(void)
{
    inputStream = NULL;
}

////////////////////////////////////////////////////////////////////////////////
StompCommandReader::StompCommandReader( InputStream* is )
{
    inputStream = is;
}

////////////////////////////////////////////////////////////////////////////////
Command* StompCommandReader::readCommand(void) 
    throw ( CommandIOException )
{
    try
    {
        // Create a new Frame for reading to.
        StompFrame* frame = new StompFrame();
       
        // Read the command header.
        readStompCommandHeader( *frame );
       
        // Read the headers.
        readStompHeaders( *frame );
       
        // Read the body.
        readStompBody( *frame );
       
        // Return the Command, caller must delete it.
        return marshaler.marshal( frame );
    }
    AMQ_CATCH_RETHROW( CommandIOException )
    AMQ_CATCH_EXCEPTION_CONVERT( ActiveMQException, CommandIOException )
    AMQ_CATCHALL_THROW( CommandIOException )
}

////////////////////////////////////////////////////////////////////////////////
void StompCommandReader::readStompCommandHeader( StompFrame& frame ) 
   throw ( CommandIOException )
{  
    try{
        while( true ) 
        {
            // The command header is formatted
            // just like any other stomp header.
            readStompHeaderLine();
    
            // Ignore all white space before the command.
            int offset = -1;
            for( size_t ix = 0; ix < buffer.size()-1; ++ix )
            {
                // Find the first non whitespace character
                if( !Character::isWhitespace(buffer[ix]) ){
                    offset = ix;
                    break;
                }
            }
        
            if( offset >= 0 )
            {
                // Set the command in the frame - copy the memory.
                frame.setCommand( reinterpret_cast<char*>(&buffer[offset]) );
                break;
            }
        
        }
    }
    AMQ_CATCH_RETHROW( CommandIOException )
    AMQ_CATCH_EXCEPTION_CONVERT( IOException, CommandIOException )
    AMQ_CATCHALL_THROW( CommandIOException )
}

////////////////////////////////////////////////////////////////////////////////
void StompCommandReader::readStompHeaders( StompFrame& frame ) 
   throw ( CommandIOException )
{
    try{
        // Read the command;
        bool endOfHeaders = false;
    
        while( !endOfHeaders )
        {        
            // Read in the next header line.
            int numChars = readStompHeaderLine();
    
            if( numChars == 0 )
            {
                // should never get here
                throw StompConnectorException(
                    __FILE__, __LINE__,
                    "StompCommandReader::readStompHeaders: no characters read" );
            }
          
            // Check for an empty line to demark the end of the header section.
            // if its not the end then we have a header to process, so parse it.
            if( numChars == 1 && buffer[0] == '\0' )
            {
                endOfHeaders = true;
            }
            else
            {
                // Search through this line to separate the key/value pair.
                for( size_t ix = 0; ix < buffer.size(); ++ix )
                {
                    // If found the key/value separator...
                    if( buffer[ix] == ':' )
                    {
                        // Null-terminate the key.
                        buffer[ix] = '\0'; 
    
                        const char* key = reinterpret_cast<char*>(&buffer[0]);
                        const char* value = reinterpret_cast<char*>(&buffer[ix+1]);
                   
                        // Assign the header key/value pair.
                        frame.getProperties().setProperty(key, value);
                   
                        // Break out of the for loop.
                        break;
                    }
                }
            }
        }
    }
    AMQ_CATCH_RETHROW( CommandIOException )
    AMQ_CATCH_EXCEPTION_CONVERT( IOException, CommandIOException )
    AMQ_CATCHALL_THROW( CommandIOException )
}

////////////////////////////////////////////////////////////////////////////////
int StompCommandReader::readStompHeaderLine(void) 
    throw ( CommandIOException )
{
    try{
        // Clear any data from the buffer.
        buffer.clear();
            
        int count = 0;
      
        while( true )
        {
            // Read the next char from the stream.
            buffer.push_back( inputStream->read() );
          
            // Increment the position pointer.
            count++;
          
            // If we reached the line terminator, return the total number
            // of characters read.
            if( buffer[count-1] == '\n' )
            {
                // Overwrite the line feed with a null character. 
                buffer[count-1] = '\0';
             
                return count;
            }
        }
       
        // If we get here something bad must have happened.
        throw StompConnectorException(
            __FILE__, __LINE__,
            "StompCommandReader::readStompHeaderLine: "
            "Unrecoverable, error condition");
    }
    AMQ_CATCH_EXCEPTION_CONVERT( IOException, CommandIOException )
    AMQ_CATCHALL_THROW( CommandIOException )
}

////////////////////////////////////////////////////////////////////////////////
void StompCommandReader::readStompBody( StompFrame& frame ) 
   throw ( CommandIOException )
{
    try{
        // Clear any data from the buffer.
        buffer.clear();
        
        unsigned long content_length = 0;
       
        if(frame.getProperties().hasProperty(
            commands::CommandConstants::toString(
                commands::CommandConstants::HEADER_CONTENTLENGTH)))
        {
            char* stopped_string = NULL;
          
            string length = 
                frame.getProperties().getProperty(
                    commands::CommandConstants::toString(
                        commands::CommandConstants::HEADER_CONTENTLENGTH));
                
            content_length = strtoul(
                length.c_str(), 
                &stopped_string, 
                10 );
         }
    
         if( content_length != 0 )
         {
            // For this case its assumed that content length indicates how 
            // much to read.  We reserve space in the buffer for it to 
            // minimize the number of reallocs that might occur.  We are
            // assuming that content length doesn't count the trailing null
            // that indicates the end of frame.  The reserve won't do anything
            // if the buffer already has that much capacity.  The resize call
            // basically sets the end iterator to the correct location since
            // this is a char vector and we already reserve enough space.
            // Resize doesn't realloc the vector smaller if content_length
            // is less than capacity of the buffer, it just move the end
            // iterator.  Reserve adds the benefit that the mem is set to 
            // zero.  Over time as larger messages come in thsi will cause
            // us to adapt to that size so that future messages that are
            // around that size won't alloc any new memory.
    
            buffer.reserve( content_length );
            buffer.resize( content_length );
    
            // Read the Content Length now
            read( &buffer[0], content_length );
    
            // Content Length read, now pop the end terminator off (\0\n).
            if(inputStream->read() != '\0' )
            {
                throw StompConnectorException(
                    __FILE__, __LINE__,
                    "StompCommandReader::readStompBody: "
                    "Read Content Length, and no trailing null");
            }
        }
        else
        {
            // Content length was either zero, or not set, so we read until the
            // first null is encounted.
          
            while( true )
            {
                char byte = inputStream->read();
             
                buffer.push_back(byte);
            
                content_length++;
    
                if( byte != '\0' )
                {            
                    continue;
                }
    
                break;  // Read null and newline we are done.
            }
        }
    
        if( content_length != 0 )
        {
            char* cpyBody = new char[content_length];
            memcpy( cpyBody, &buffer[0], content_length );
    
            // Set the body contents in the frame - copy the memory
            frame.setBody( cpyBody, content_length );
        }    
    }
    AMQ_CATCH_EXCEPTION_CONVERT( IOException, CommandIOException )
    AMQ_CATCHALL_THROW( CommandIOException )
}

////////////////////////////////////////////////////////////////////////////////
int StompCommandReader::read( unsigned char* buffer, int count ) 
   throw( io::IOException )
{
    try{
        if( inputStream == NULL )
        {
            throw IOException( 
                __FILE__, __LINE__, 
                "StompCommandReader::read(char*,int) - input stream is NULL" );
        }
       
        // Just delegate to the input stream.
        return inputStream->read( buffer, count );
    }
    AMQ_CATCH_RETHROW( IOException )
    AMQ_CATCHALL_THROW( IOException )
}
 
////////////////////////////////////////////////////////////////////////////////
unsigned char StompCommandReader::readByte(void) throw( io::IOException )
{
        try{
        if( inputStream == NULL )
        {
            throw IOException( 
                __FILE__, __LINE__, 
                "StompCommandReader::read(char*,int) - input stream is NULL" );
        }
       
        return inputStream->read();
    }
    AMQ_CATCH_RETHROW( IOException )
    AMQ_CATCHALL_THROW( IOException )
}
