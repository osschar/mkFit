TTree t;

static const unsigned int algorithms[]={ 4,22,23,5,24,7,8,9,10 }; //9 iterations
static const char* names[] = { "undefAlgorithm", "ctf", "duplicateMerge",
"cosmics", "initialStep", "lowPtTripletStep", "pixelPairStep", "detachedTripletStep",
"mixedTripletStep", "pixelLessStep", "tobTecStep", "jetCoreRegionalStep", "conversionStep",
"muonSeededStepInOut", "muonSeededStepOutIn", "outInEcalSeededConv", "inOutEcalSeededConv",
"nuclInter", "standAloneMuon", "globalMuon", "cosmicStandAloneMuon", "cosmicGlobalMuon",
"highPtTripletStep", "lowPtQuadStep", "detachedQuadStep", "reservedForUpgrades1",
"reservedForUpgrades2", "bTagGhostTracks", "beamhalo", "gsf", "hltPixel", "hltIter0",
"hltIter1", "hltIter2", "hltIter3", "hltIter4", "hltIterX", "hiRegitMuInitialStep",
"hiRegitMuLowPtTripletStep", "hiRegitMuPixelPairStep", "hiRegitMuDetachedTripletStep",
"hiRegitMuMixedTripletStep", "hiRegitMuPixelLessStep", "hiRegitMuTobTecStep",
"hiRegitMuMuonSeededStepInOut", "hiRegitMuMuonSeededStepOutIn", "algoSize" };

void select_iter(int i)
{
    TString c( TString::Format("iter == %d", i));
    t.SetEventList(0);
    t.Draw(">>iter_eli", c);
    t.SetEventList( (TEventList*)gDirectory->Get("iter_eli") );
}

void bigtxt()
{
    printf("1 %p\n", gPad);
    printf("2 %p\n", gPad->GetListOfPrimitives());
    printf("3 %p\n", gPad->GetListOfPrimitives()->At(1));
    printf("Bigtexting %s\n", gPad->GetListOfPrimitives()->At(1)->ClassName());
    auto h = dynamic_cast<TH1*>(gPad->GetListOfPrimitives()->At(1));
    h->SetMarkerSize(3);
    h->GetYaxis()->SetRangeUser(0, 1.1 * h->GetMaximum());
    gPad->Modified(); gPad->Update();
}

void draw(const char *sexp)
{
    t.Draw(sexp, 0, "HIST TEXT45");
    // gPad->Modified();
    gPad->Update();
    // gSystem->ProcessEvents();
    bigtxt();
}

TCanvas* draw_stuff(const char* canvas_name)
{
    auto c = new TCanvas(canvas_name, canvas_name);
    c->Divide(2, 2);
    int i = 0;
    c->cd(++i);
    draw("n_ovlp_hits_added");
    c->cd(++i);
    draw("n_ovlp_hits_bad / n_ovlp_hits_added");
    c->cd(++i);
    draw("n_ovlp_hits_same_module");
    c->cd(++i);
    draw("n_ovlp_hits_same_module_bad / n_ovlp_hits_same_module");
    
    return c;
}

void seedmrg()
{
    t.SetDirectory(gDirectory);
    t.ReadFile("smrg.rtt");

    {
        auto c = new TCanvas("0_SeedsPerIter", "0_SeedsPerIter");
        draw("iter");
        c->SaveAs(".png");
    }

    draw_stuff("0_All_Iterations")->SaveAs(".png");

    for (int i = 0; i <= 6; ++i)
    {
        select_iter(i);
        auto c = draw_stuff(TString::Format("Iteration_%d_%d_%s", i, algorithms[i], names[algorithms[i]]));
        c->SaveAs(".png");
    }
}



/*

t.Draw("n_ovlp_hits_good")
root [4] t.Draw("n_ovlp_hits_badInfo in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1_n3

root [5] Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1_n4

root [5] t.Draw("n_ovlp_hits_shared")
root [6] t.Draw("n_ovlp_hits_same_module")
root [7] t.Draw("n_ovlp_hits_same_module_good")
root [8] t.Draw("n_ovlp_hits_same_module_bad")
root [9]
root [9] t.Draw("n_ovlp_hits_same_module_bad", "TEXT")
Error in <TTreeFormula::Compile>:  Bad numerical expression : "TEXT"
Info in <TSelectorDraw::AbortProcess>: Variable compilation failed: {n_ovlp_hits_same_module_bad,TEXT}
(long long) -1
root [10] t.Draw("n_ovlp_hits_same_module_bad", "TXT")
Error in <TTreeFormula::Compile>:  Bad numerical expression : "TXT"
Info in <TSelectorDraw::AbortProcess>: Variable compilation failed: {n_ovlp_hits_same_module_bad,TXT}
(long long) -1
root [11] t.Draw("n_ovlp_hits_same_module_bad", "TEXT0")
Error in <TTreeFormula::Compile>:  Bad numerical expression : "TEXT0"
Info in <TSelectorDraw::AbortProcess>: Variable compilation failed: {n_ovlp_hits_same_module_bad,TEXT0}
(long long) -1
root [12] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT")
(long long) 35245
root [13] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT HIST")
(long long) 35245
root [14] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT90 HIST")
(long long) 35245
root [15]
root [15] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT0 HIST")
(long long) 35245
root [16] gPad->SetMargin(
void SetMargin(Float_t left, Float_t right, Float_t bottom, Float_t top)
root [16] gStyle->SetMarkerS
SetMarkerSize
SetMarkerStyle
root [16] gStyle->SetMarkerSize(
void SetMarkerSize(Size_t msize = 1)    // Set the marker size
root [16] gStyle->SetMarkerSize(2)
root [17] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT0 HIST")
(long long) 35245
root [18] gStyle->SetMarkerSize(4)
root [19] t.Draw("n_ovlp_hits_same_module_bad", "", "TEXT0 HIST")
(long long) 35245
root [20] t.Draw("n_ovlp_hits_same_module_bad>>hh", "", "TEXT0 HIST")

root [21] hh->SetMarkerSize(4)
root [22] hh->Draw()
root [23] hh->Draw("TEXT0 HIST")

*/
