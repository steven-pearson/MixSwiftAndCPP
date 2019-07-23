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
    typealias PublisherType = AnyPublisher<String, Never>
    
    var model : TimeInfo
    
    let willChange : PublisherType
    
    override init() {
        self.model = TimeInfo()
        
        willChange = self.model.publisher(for: \.currentTime)
            .receive(on: RunLoop.main)
            .eraseToAnyPublisher()
    }
}
