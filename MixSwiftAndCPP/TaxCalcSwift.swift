//
//  TaxCalcSwift.swift
//  MixSwiftAndCPP
//
//  Created by Steven Pearson on 27/07/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import Foundation

class TaxCalcSwift : NSObject {
    
    let cppObject = UnsafeMutableRawPointer(mutating: createInstance())
    
    @objc dynamic var net: Double {
        get {
            getNet(cppObject)
        }
        set {
            setNet(cppObject, newValue)
        }
    }
    
    @objc dynamic var taxRate: Double {
        get {
            getTaxRate(cppObject)
        }
        set {
            setTaxRate(cppObject, newValue)
        }
    }


    @objc dynamic var tax: Double {
        get {
            return getTax(cppObject)
        }
        set {
            setTax(cppObject, newValue)
        }
    }

    @objc dynamic var gross: Double {
        get {
            return getGross(cppObject)
        }
    }
}
