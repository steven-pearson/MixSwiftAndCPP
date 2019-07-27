//
//  ContentView.swift
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 13/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

import SwiftUI

struct ContentView : View {
    @ObjectBinding var viewModel : TaxCalcViewModel
    
    private let currencyFormatter: NumberFormatter = {
        let f = NumberFormatter()
        f.numberStyle = .currency
        return f
    }()
    
    var body: some View {
        VStack{
            TextField("Net", value:$viewModel.model.net, formatter:currencyFormatter)
                .font(.largeTitle)
            TextField("Tax", value:$viewModel.model.tax, formatter:currencyFormatter)
                .font(.largeTitle)
            TextField("Gross", value:$viewModel.model.gross, formatter:currencyFormatter)
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
