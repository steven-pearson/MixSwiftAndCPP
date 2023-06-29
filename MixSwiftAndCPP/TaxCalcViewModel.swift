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
        
    @Published var model : TaxCalcSwift

    let currencyFormatter: NumberFormatter = {
        let f = NumberFormatter()
        f.numberStyle = .decimal
        f.maximumFractionDigits = 2
        f.minimumFractionDigits = 2
        return f
    }()
    
    override init() {
        model = TaxCalcSwift()
        super.init()
        
        //model.net = 100;
        model.taxRate = 0.2;
    }

    var gross: String {
        get {
            return currencyFormatter.string(from: NSNumber.init(value: model.gross))!
        }
    }
}
