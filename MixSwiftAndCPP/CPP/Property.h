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

    class IPropertyChangeNotification {
    public:
        virtual void OnPropertyChanging(CPropertyChangingEventArgs& args) const = 0;
        virtual void OnPropertyChanged(CPropertyChangedEventArgs& args) const = 0;
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

        CProperty(const char* name, IPropertyChangeNotification* container, Getter getter, Setter setter) : CPropertyBase(name) {
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
                
                if (_get != NULL) {
                    TValueType oldValue = _get();
                    propertyChanging = (oldValue != value);
                }

                if (propertyChanging) {
                    OnChanging();
                    _set(value);
                    OnChanged();
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
        
        CEventBase<CPropertyChangingEventArgs> Changing;
        CEventBase<CPropertyChangedEventArgs> Changed;
        
        void OnChanging() {
            // TODO Add the ability to cancel here by adding some event args and a cancel option
            
            CPropertyChangingEventArgs args(name());
            if (_container) {
                _container->OnPropertyChanging(args);
            }
            Changing.Notify(args);
            
            // TODO If cancel, put the original value back etc
        }
        
        void OnChanged() {
            CPropertyChangedEventArgs args(name());
            Changed.Notify(args);
            if (_container) {
                _container->OnPropertyChanged(args);
            }
        }

    protected:
        IPropertyChangeNotification* _container;
        
    private:
        Setter _set;
        Getter _get;
    };
//}

#pragma pack(pop)

#endif
