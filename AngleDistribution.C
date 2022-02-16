void AngleDistribution(){
  TFile *rootfile = TFile::Open("lumi_t0.root");
  
  lumi->SetAlias("theta","atan(sqrt((hit_x)**2+(hit_y)**2)/(hit_z+110))*180/3.1415");
  
  int nbin = 20000;
  int bin_max = 2;
  double bin_size = (double)bin_max/nbin;
  TH1D *h_theta = new TH1D("h_theta","",nbin,0,bin_max);
  lumi->Draw("theta>>h_theta","(detID==1&& particleID==1 && Ekin>2)");

  double radi[8];
  double angle_min_old[8];
  double angle_max_old[8];
  double angle_min_new[8];
  double angle_max_new[8];

  double dist_old = 805;
  double dist_new = 810;
  
  double rate_old[8];
  double rate_new[8];
  int bin_up;
  int bin_low;
  cout << "" << endl;
  for(int i=0;i<8;i++){
    radi[i] = 3.5 +i;
    angle_min_new[i] = TMath::ATan(radi[i]/dist_new)*180/3.14;
    angle_max_new[i] = TMath::ATan((radi[i]+1.25)/dist_new)*180/3.14;
    angle_min_old[i] = TMath::ATan(radi[i]/dist_old)*180/3.14;
    angle_max_old[i] = TMath::ATan((radi[i]+1.25)/dist_old)*180/3.14;
    
    bin_low = angle_min_old[i]/bin_size;
    bin_up = angle_max_old[i]/bin_size;
    rate_old[i] = h_theta->Integral(bin_low,bin_up)/radi[i];

    bin_low = angle_min_new[i]/bin_size;
    bin_up = angle_max_new[i]/bin_size;
    rate_new[i] = h_theta->Integral(bin_low,bin_up)/radi[i];
    
    printf("%.1f \t [%.4f,%.4f] \t %E \t [%.4f,%.4f] \t %E \n",
	   radi[i],angle_min_old[i],angle_max_old[i],rate_old[i],
	   angle_min_new[i],angle_max_new[i],rate_new[i]);
    
    TMultiGraph *mg = new TMultiGraph();
    TGraph *g1 = new TGraph(8,radi,rate_new);
    TGraph *g2 = new TGraph(8,radi,rate_old);
    g1->SetMarkerStyle(20);
    g2->SetMarkerStyle(20);
    mg->Add(g1,"p");
    mg->Add(g2,"p");
    mg->Draw("AP");

  }
}
