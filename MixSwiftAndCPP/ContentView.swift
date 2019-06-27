//
//  ContentView.swift
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 13/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import SwiftUI


struct ContentView : View {
    @ObjectBinding var viewModel : ClockViewModel
    var body: some View {
        Text(viewModel.model.currentTime)
            .font(.largeTitle)
    }
}

#if DEBUG
struct ContentView_Previews : PreviewProvider {
    static var previews: some View {
        ContentView(viewModel: ClockViewModel())
    }
}
#endif
