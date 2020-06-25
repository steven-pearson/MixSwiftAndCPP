//
//  TaxCalcViewModel.swift
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import Foundation
import SwiftUI
import Combine

class TaxCalcViewModel : NSObject, ObservableObject {
        
    //@Published var model : TaxCalcBridge
    @Published var model : TaxCalcSwift
    let cppObject = UnsafeMutableRawPointer(mutating: createInstance())

    let currencyFormatter: NumberFormatter = {
        let f = NumberFormatter()
        f.numberStyle = .currency
        return f
    }()
    
    var gross: String {
        get {
            print("Getting gross")
            return currencyFormatter.string(from: NSNumber.init(value: model.gross))!
        }
    }

    
    //var willChange: PublisherType
    
    //private var myContext = 0
    
    //var kvoToken: NSKeyValueObservation?

    override init() {
        //model = TaxCalcBridge()
        model = TaxCalcSwift()
        super.init()
        
        model.net = 100;
        model.taxRate = 0.2;

/*        willChange = model.publisher(for: \.gross)
            .receive(on: RunLoop.main)
            .eraseToAnyPublisher()*/
        
        /*kvoToken = model.observe(\.gross, options: .new) { (person, change) in
            guard let gross = change.newValue else { return }
            print("New gross is: \(gross)")
        }
        
        model.addObserver(self, forKeyPath: "gross", options: .new, context: &myContext)*/
    }
    
    /*override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        if context == &myContext {
            if let newValue = change?[NSKeyValueChangeKey.newKey] {
                print("\(String(describing: keyPath)) changed: \(newValue)")
                //willChange.eraseToAnyPublisher()
            }
        } else {
            //super.observeValue(keyPath, Object: object, change: change, context: context)
        }

    }

    deinit {
        model.removeObserver(self, forKeyPath: "gross", context: &myContext)
        kvoToken?.invalidate()
    }*/
    
}
