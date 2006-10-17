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

#ifndef _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_CONSUMERINFO_H_
#define _ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_CONSUMERINFO_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/connector/openwire/commands/BaseCommand.h>
#include <activemq/connector/openwire/commands/ConsumerId.h>
#include <activemq/connector/openwire/commands/ActiveMQDestination.h>
#include <activemq/connector/openwire/commands/BrokerId.h>
#include <activemq/connector/openwire/commands/BooleanExpression.h>
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
    class ConsumerInfo : public BaseCommand
    {
    protected:

        ConsumerId* consumerId;
        bool browser;
        ActiveMQDestination* destination;
        int prefetchSize;
        int maximumPendingMessageLimit;
        bool dispatchAsync;
        std::string selector;
        std::string subcriptionName;
        bool noLocal;
        bool exclusive;
        bool retroactive;
        char priority;
        std::vector<BrokerId*> brokerPath;
        BooleanExpression* additionalPredicate;
        bool networkSubscription;
        bool optimizedAcknowledge;
        bool noRangeAcks;

    public:

        const static unsigned char ID_CONSUMERINFO = 5;

    public:

        ConsumerInfo();
        virtual ~ConsumerInfo();

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
        virtual ConsumerInfo* clone() const;

        /**
         * Copy the contents of this object and place them into the
         * instance of this object type that was passed in.
         * @return dest - Destination Object
         */
        virtual void clone( ConsumerInfo* dest ) const;

        virtual const ConsumerId* getConsumerId() const;
        virtual ConsumerId* getConsumerId();
        virtual void setConsumerId( ConsumerId* consumerId );

        virtual const bool getBrowser() const;
        virtual bool getBrowser();
        virtual void setBrowser( bool browser );

        virtual const ActiveMQDestination* getDestination() const;
        virtual ActiveMQDestination* getDestination();
        virtual void setDestination( ActiveMQDestination* destination );

        virtual const int getPrefetchSize() const;
        virtual int getPrefetchSize();
        virtual void setPrefetchSize( int prefetchSize );

        virtual const int getMaximumPendingMessageLimit() const;
        virtual int getMaximumPendingMessageLimit();
        virtual void setMaximumPendingMessageLimit( int maximumPendingMessageLimit );

        virtual const bool getDispatchAsync() const;
        virtual bool getDispatchAsync();
        virtual void setDispatchAsync( bool dispatchAsync );

        virtual const std::string& getSelector() const;
        virtual std::string& getSelector();
        virtual void setSelector( const std::string& selector );

        virtual const std::string& getSubcriptionName() const;
        virtual std::string& getSubcriptionName();
        virtual void setSubcriptionName( const std::string& subcriptionName );

        virtual const bool getNoLocal() const;
        virtual bool getNoLocal();
        virtual void setNoLocal( bool noLocal );

        virtual const bool getExclusive() const;
        virtual bool getExclusive();
        virtual void setExclusive( bool exclusive );

        virtual const bool getRetroactive() const;
        virtual bool getRetroactive();
        virtual void setRetroactive( bool retroactive );

        virtual const char getPriority() const;
        virtual char getPriority();
        virtual void setPriority( char priority );

        virtual const std::vector<BrokerId*> getBrokerPath() const;
        virtual std::vector<BrokerId*> getBrokerPath();
        virtual void setBrokerPath( std::vector<BrokerId*> brokerPath );

        virtual const BooleanExpression* getAdditionalPredicate() const;
        virtual BooleanExpression* getAdditionalPredicate();
        virtual void setAdditionalPredicate( BooleanExpression* additionalPredicate );

        virtual const bool getNetworkSubscription() const;
        virtual bool getNetworkSubscription();
        virtual void setNetworkSubscription( bool networkSubscription );

        virtual const bool getOptimizedAcknowledge() const;
        virtual bool getOptimizedAcknowledge();
        virtual void setOptimizedAcknowledge( bool optimizedAcknowledge );

        virtual const bool getNoRangeAcks() const;
        virtual bool getNoRangeAcks();
        virtual void setNoRangeAcks( bool noRangeAcks );

    };

}}}}

#endif /*_ACTIVEMQ_CONNECTOR_OPENWIRE_COMMANDS_CONSUMERINFO_H_*/

