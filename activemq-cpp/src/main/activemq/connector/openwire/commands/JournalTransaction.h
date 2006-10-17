/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALTRANSACTION_H_
#define _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALTRANSACTION_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/connector/openwire/commands/BaseDataStructure.h>
#include <activemq/connector/openwire/commands/TransactionId.h>
#include <vector>
#include <string>

namespace activemq{
namespace connector{
namespace openwire{
namespace commands{

    /*
     *
     *  Command and marshalling code for OpenWire format for ${className}
     *
     *
     *  NOTE!: This file is autogenerated - do not modify!
     *         if you need to make a change, please see the Java Classes
     *         in the activemq-openwire-generator module
     *
     */
    class JournalTransaction : public BaseDataStructure
    {
    protected:

        TransactionId* transactionId;
        char type;
        bool wasPrepared;

    public:

        const static unsigned char ID_JOURNALTRANSACTION = 54;

    public:

        JournalTransaction();
        virtual ~JournalTransaction();

        /**
         * Get the unique identifier that this object and its own
         * Marshaller share.
         * @returns new DataStructure type copy.
         */
        virtual unsigned char getDataStructureType() const;

        /**
         * Clone this obbject and return a new instance that the
         * caller now owns, this will be an exact copy of this one
         * @returns new copy of this object.
         */
        virtual JournalTransaction* clone() const;

        /**
         * Copy the contents of this object and place them into the
         * instance of this object type that was passed in.
         * @return dest - Destination Object
         */
        virtual void clone( JournalTransaction* dest ) const;

        virtual const TransactionId* getTransactionId() const;
        virtual TransactionId* getTransactionId();
        virtual void setTransactionId( TransactionId* transactionId );

        virtual const char getType() const;
        virtual char getType();
        virtual void setType( char type );

        virtual const bool getWasPrepared() const;
        virtual bool getWasPrepared();
        virtual void setWasPrepared( bool wasPrepared );

    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_JOURNALTRANSACTION_H_*/

