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

#ifndef _ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_ACKCOMMANDTEST_H_
#define _ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_ACKCOMMANDTEST_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <activemq/connector/stomp/commands/AckCommand.h>

namespace activemq{
namespace connector{
namespace stomp{
namespace commands{
            
    class AckCommandTest : public CppUnit::TestFixture
    {
        CPPUNIT_TEST_SUITE( AckCommandTest );
        CPPUNIT_TEST( test );
        CPPUNIT_TEST_SUITE_END();

    public:

    	AckCommandTest() {}
    	virtual ~AckCommandTest() {}

        void test(void)
        {
            AckCommand cmd;

            CPPUNIT_ASSERT( cmd.getStompCommandId() == 
                            CommandConstants::ACK );
            
            CPPUNIT_ASSERT( cmd.isResponseRequired() == false );
            cmd.setResponseRequired( true );
            cmd.setCommandId( 123 );
            CPPUNIT_ASSERT( cmd.isResponseRequired() == true );
            CPPUNIT_ASSERT( cmd.getCommandId() == 123 );
            cmd.setCorrelationId( 99 );
            CPPUNIT_ASSERT( cmd.getCorrelationId() == 99 );
            CPPUNIT_ASSERT( cmd.getTransactionId() == "" );
            cmd.setTransactionId( "ID:123456" );
            CPPUNIT_ASSERT( std::string( cmd.getTransactionId() ) == 
                            "ID:123456" );
            CPPUNIT_ASSERT( cmd.getMessageId() == "" );
            cmd.setMessageId( "ID:123456789" );
            CPPUNIT_ASSERT( std::string( cmd.getMessageId() ) == "ID:123456789" );
            
            StompFrame* frame = cmd.marshal().clone();
            
            CPPUNIT_ASSERT( frame != NULL );
            
            AckCommand cmd1( frame );
            
            CPPUNIT_ASSERT( cmd.getCommandId() == cmd1.getCommandId() );
            CPPUNIT_ASSERT( cmd.getStompCommandId() == cmd1.getStompCommandId() );
            CPPUNIT_ASSERT( cmd.isResponseRequired() == cmd1.isResponseRequired() );
            CPPUNIT_ASSERT( cmd.getCorrelationId() == cmd1.getCorrelationId() );
            CPPUNIT_ASSERT( cmd.getMessageId() == cmd1.getMessageId() );
            CPPUNIT_ASSERT( cmd.getTransactionId() == cmd1.getTransactionId() );
            
        }
    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_STOMP_COMMANDS_ACKCOMMANDTEST_H_*/
