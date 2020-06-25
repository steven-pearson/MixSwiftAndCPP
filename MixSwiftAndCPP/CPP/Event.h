//
//  Event.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#ifndef __Event_h
#define __Event_h

#pragma once

#include <map>
#include <string>
#include <exception>
#include <functional>

//namespace legacy {
    typedef unsigned int EventHandlerID;
    
    struct event_exception: std::exception {
        event_exception (const std::string& what) { _what = what; }
        ~event_exception () throw () {}
        
        const char*
        what () const throw () { return _what.c_str(); }
        
    private:
        std::string _what;
    };
    
    class CEventArgs {
    public:
        CEventArgs(bool canStop = false) : _canStop(canStop) {
            _stop = false;
        }
        
        const bool CanStop() const { return _canStop; }
        
        const bool IsStopSet() const { return _stop; }
        
        void SetFailureInfo(bool stop, const std::string& failureCode, const std::string& failureReason) {
            _failureCode = failureCode;
            _failureReason = failureReason;
            _stop = stop;
        }
        
        const std::string& GetFailureReason() const { return _failureReason; }
        
    private:
        std::string _failureCode;
        std::string _failureReason;
        bool _stop;
        const bool _canStop;
    };

    class CNotifyPropertyChangingEventArgs : public CEventArgs {
        
    public:
        CNotifyPropertyChangingEventArgs(const std::string& name) :
            _name(name) {
        }
        
        const std::string& name() const { return _name; }
        
    private:
        const std::string& _name;
    };

    class CNotifyPropertyChangedEventArgs : public CEventArgs {
        
    public:
        CNotifyPropertyChangedEventArgs(const std::string& name) : _name(name) {
        }
        
        const std::string& name() const { return _name; }
        
    private:
        const std::string& _name;
    };

    template<typename ParamT>
    class CPropertyChangingEventArgs : public CEventArgs {
        
    public:
        CPropertyChangingEventArgs(const ParamT& proposedValue, const std::string& name) :
            _proposedValue(proposedValue),
            _name(name) {
        }
        
        const std::string& name() const { return _name; }
        const ParamT& proposedValue() const { return _proposedValue; }

    private:
        const std::string& _name;
        const ParamT& _proposedValue;
    };

    template<typename ParamT>
    class CPropertyChangedEventArgs : public CEventArgs {
        
    public:
        CPropertyChangedEventArgs(const ParamT& newValue, const std::string& name) :
            _newValue(newValue),
            _name(name) {
        }
        
        const std::string& name() const { return _name; }
        const ParamT& newValue() const { return _newValue; }

    private:
        const std::string& _name;
        const ParamT& _newValue;
    };

    template<typename ParamT>
    class CEventHandlerBase {
    public:
        virtual void Notify(CEventArgs& eventArgs) const = 0;
        virtual ~CEventHandlerBase() {};
    };

    //template<typename EventArgsT>
    //typedef std::function<void(EventArgsT&)> EventHandler;

    template<typename EventArgsT>
    class CEventHandler : public CEventHandlerBase<EventArgsT> {
        void *_context;
        std::function<void(EventArgsT&)> _eventHandler;
        
    public:
        CEventHandler(void *context, std::function<void(EventArgsT&)> eventHandler)
        : _context(context), _eventHandler(eventHandler)
        {
        }

        void Notify(EventArgsT& eventArgs) const {
            return (_eventHandler)();
        }
    };

    template<typename EventArgsT>
    class CEventBase {
        typedef std::map <EventHandlerID, std::function<void(EventArgsT&)>> HandlerMap;
        HandlerMap _eventHandlers;
        EventHandlerID _count;
        
    public:
        CEventBase()
            : _count(0)
        {
        }
        
        ~CEventBase() {
        }
        
        EventHandlerID Subscribe(std::function<void(EventArgsT&)> const &block) {
            _eventHandlers[_count++] = block;
            return _count-1;
        }
        
        void Unsubscribe(EventHandlerID handlerId) {
            _eventHandlers.erase(handlerId);
        }
        
        void Notify(EventArgsT eventArgs) const {
            // Iterate through the handlers calling each one in turn
            for (unsigned int index=0; index < _count && index < _eventHandlers.size(); index++) {
                _eventHandlers.find(index)->second(eventArgs);
                if (eventArgs.IsStopSet()) {
                    throw event_exception(eventArgs.GetFailureReason());
                    break;
                }
            }
        }
    };
//}

#endif

