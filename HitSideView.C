void HitSideView(){
  TFile *rootfile = TFile::Open("lumi_chained.root");

  TCanvas *c1 = new TCanvas("c1","c1",800,800);
  TCanvas *c2 = new TCanvas("c2","c2",800,800);
  
  lumi->Draw("hit_x:hit_z>>h1(50,699,701,50,-10,10)","detID>10 && particleID==2 && Ekin>2", "goff");
  lumi->Draw("hit_y:hit_z>>h2(50,699,701,50,-10,10)","detID>10 && particleID==2 && Ekin>2", "goff");

  c1->cd();
  h1->SetTitle("SAM Electron Hit, Top View: X vs Z");
  h1->GetYaxis()->SetTitle("X(cm)");
  h1->GetXaxis()->SetTitle("Z(cm)");
  h1->Draw("COLZ");

  c2->cd();
  h2->SetTitle("SAM Electron Hit, Side View: Y vs Z");
  h2->GetYaxis()->SetTitle("Y(cm)");
  h2->GetXaxis()->SetTitle("Z(cm)");
  h2->Draw("COLZ");

  c1->SaveAs("topview.pdf");
  c2->SaveAs("sideview.pdf");
}
