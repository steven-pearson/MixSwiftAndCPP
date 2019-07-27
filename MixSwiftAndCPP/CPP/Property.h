//
//  Property.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#ifndef __Property_h
#define __Property_h

#pragma once

#include "Event.h"
#include <utility>
#include <assert.h>
#include <string>
#include <functional>

#pragma pack(push, 1)

//namespace legacy {

    class INotifyPropertyChange {
    public:
        virtual void OnPropertyChanging(CNotifyPropertyChangingEventArgs& args) const = 0;
        virtual void OnPropertyChanged(CNotifyPropertyChangedEventArgs& args) const = 0;
    };

    class CPropertyBase {
    public:
        CPropertyBase(const std::string& name) : _name(name) {
        }

        const std::string& name() const {
            return _name;
        }
        
    private:
        const std::string _name;
    };

    template <typename TValueType>
    class CProperty : public CPropertyBase {

    public:
        typedef std::function<TValueType()> Getter;
        typedef std::function<void(TValueType)> Setter;

        CProperty(const char* name, INotifyPropertyChange* container, Getter getter, Setter setter = NULL) : CPropertyBase(name) {
            _container = container;
            _set = setter;
            _get = getter;
        }

    #pragma warning (push)
    #pragma warning (disable : 4181 )
        //-- Overload the = operator to set the value using the set member --
        void operator =(TValueType value) {
            if (_set != NULL) {
                bool propertyChanging = true;
                TValueType oldValue = _get();

                propertyChanging = (oldValue != value);

                if (propertyChanging) {
                    OnChanging(oldValue);
                    _set(value);
                    OnChanged(value);
                }
            }
        }
    #pragma warning (pop)

        //-- Cast the property class to the internal type --
        operator TValueType() {
            try {
                return _get != NULL ? _get() : DefaultGetter();
            }
            catch(...) {
                return DefaultGetter();
            }
        }
        
        const TValueType DefaultGetter() const {
            return TValueType(NULL);
        }
        
        CEventBase<CPropertyChangingEventArgs<TValueType>> Changing;
        
        CEventBase<CPropertyChangedEventArgs<TValueType>> Changed;
        
        void OnChanging(const TValueType &proposedValue) {
            // TODO Add the ability to cancel here by adding some event args and a cancel option
            
            CPropertyChangingEventArgs<TValueType> args(proposedValue, name());
            if (_container) {
                CNotifyPropertyChangingEventArgs notifyArgs(name());
                _container->OnPropertyChanging(notifyArgs);
            }
            Changing.Notify(args);
            
            // TODO If cancel, put the original value back etc
        }
        
        void OnChanged(const TValueType &newValue) {
            CPropertyChangedEventArgs<TValueType> args(newValue, name());
            Changed.Notify(args);
            if (_container) {
                CNotifyPropertyChangedEventArgs notifyArgs(name());
                _container->OnPropertyChanged(notifyArgs);
            }
        }

    protected:
        INotifyPropertyChange* _container;
        
    private:
        Setter _set;
        Getter _get;
    };
//}

#pragma pack(pop)

#endif
