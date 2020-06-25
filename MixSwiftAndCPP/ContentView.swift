//
//  ContentView.swift
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 13/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import SwiftUI

struct ContentView : View {
    @ObservedObject var viewModel : TaxCalcViewModel
    
    var body: some View {
        VStack{
            TextField("Net", value:$viewModel.model.net, formatter:viewModel.currencyFormatter)
                .font(.largeTitle)
            TextField("Tax", value:$viewModel.model.tax, formatter:viewModel.currencyFormatter)
                .font(.largeTitle)
            Text(viewModel.gross)
                .font(.largeTitle)
        }
    }
}

#if DEBUG
struct ContentView_Previews : PreviewProvider {
    static var previews: some View {
        ContentView(viewModel: TaxCalcViewModel())
    }
}
#endif
