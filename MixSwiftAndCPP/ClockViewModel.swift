//
//  ClockViewModel.swift
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import Foundation
import SwiftUI
import Combine

class ClockViewModel : NSObject, BindableObject {
    
    var model : TimeInfo
    
    let didChange: AnyPublisher<String, Never>
    
    override init() {
        self.model = TimeInfo()
        
        didChange = self.model.publisher(for: \.currentTime)
            .receive(on: RunLoop.main)
            .eraseToAnyPublisher()
    }
}
