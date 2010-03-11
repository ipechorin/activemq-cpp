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

#include "String.h"

#include <decaf/lang/System.h>
#include <decaf/lang/exceptions/NullPointerException.h>

using namespace std;
using namespace decaf;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;

////////////////////////////////////////////////////////////////////////////////
namespace decaf{
namespace lang{

    class Contents {
    public:

        unsigned char* value;
        int length;
        int offset;

    public:

        Contents() : value( NULL ), length( 0 ), offset( 0 ) {
        }

        Contents( int length ) : value( new unsigned char[length] ), length( length ), offset( 0 ) {
        }

        ~Contents() {
            delete [] value;
        }

    };

}}

////////////////////////////////////////////////////////////////////////////////
String::String() {
    this->contents.reset( new Contents() );
}

////////////////////////////////////////////////////////////////////////////////
String::String( const std::string& source ) {

    // Initialize the contents object.
    this->contents.reset( new Contents( source.length() ) );

    // load the passed string into the contents value.
    System::arraycopy( (unsigned char*)source.c_str(), 0, contents->value, 0, source.length() );
}

////////////////////////////////////////////////////////////////////////////////
String::~String() {
    try{
    }
    DECAF_CATCH_NOTHROW( Exception )
    DECAF_CATCHALL_NOTHROW()
}
