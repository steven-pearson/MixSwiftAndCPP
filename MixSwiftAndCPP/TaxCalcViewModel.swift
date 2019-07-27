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

class TaxCalcViewModel : NSObject, BindableObject {
    typealias PublisherType = AnyPublisher<NSNumber, Never>
        
    var model : TaxCalc
    
    var willChange: PublisherType

    override init() {
        self.model = TaxCalc()
        self.model.net = 100;
        self.model.taxRate = 0.2;

        willChange = self.model.publisher(for: \.gross)
            .receive(on: RunLoop.main)
            .eraseToAnyPublisher()
    }
}
