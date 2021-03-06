#include <stdio.h>      /* printf */
#include <math.h>       /* sqrt */
//STANDARD ROOT INCLUDES
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TLegend.h>
#include <TDirectory.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TMatrixT.h>
#include <TVectorT.h>
//
////STANDARD C++ INCLUDES
#include <iostream>
#include <string>
#include <sstream>
//#include <vector>
#include <map>
#include <cmath>
#define PI 3.141592653589793
using namespace std;
Bool_t switchlumiweight = true;
void CEPDijetsPPS()
{
    //------------ FWLite libraries ------
    gSystem->Load("libFWCoreFWLite.so");
    AutoLibraryLoader::enable();
    gROOT->ProcessLine("#include<vector>");
    gROOT->ProcessLine(".exception"); 
    //------------ files -----------------
    //TFile *inf  = TFile::Open("ttreeCEPdijetsNoOOT_NoPU.root");
    TFile *inf  = TFile::Open("ttreeCEPdijetsNoOOT_PU.root");
    //TFile *inf  = TFile::Open("ttreeCEPdijetsOOT_PU.root");
    TFile *outf = new TFile("CEPDijets_PPS_NoOOT_PU_HistosTEST.root","RECREATE");

    TTree *tr = (TTree*)inf->Get("demo/Event");
    //----------- define the tree branch --------
    std::vector<double>  *JetsPt=0;
    std::vector<double>  *JetsEta=0;
    std::vector<double>  *JetsPhi=0;
    std::vector<double>  *JetsSameVertex_pt=0;
    std::vector<double>  *JetsSameVertex_eta=0;
    std::vector<double>  *JetsSameVertex_phi=0;
    std::vector<double>  *CandidatesJets_pt=0;
    std::vector<double>  *CandidatesJets_eta=0;
    std::vector<double>  *CandidatesJets_phi=0; 
    Double_t        VertexZPPS;
    Int_t           nVertex;
    Int_t           nTracks;
    Double_t        MinDistance;
    Double_t        MaxDistance;
    Double_t        GoldenVertexZ;
    Double_t        xiPPSArmB;
    Double_t        xiPPSArmF;
    Double_t        tPPSArmB;
    Double_t        tPPSArmF;
    Double_t        xPPSArmBDet1;
    Double_t        xPPSArmFDet1;
    Double_t        yPPSArmBDet1;
    Double_t        yPPSArmFDet1;
    Double_t        xPPSArmBDet2;
    Double_t        xPPSArmFDet2;
    Double_t        yPPSArmBDet2;
    Double_t        yPPSArmFDet2;
    Int_t           stopPPSArmFTrkDet1;
    Int_t           stopPPSArmFTrkDet2;
    Int_t           stopPPSArmBTrkDet1;
    Int_t           stopPPSArmBTrkDet2;
    Int_t           stopPPSArmFToF;
    Int_t           stopPPSArmBToF; 
    Double_t        Mjj;
    Double_t        CandidatesMjj;
    Double_t        Mpf;
    Double_t        Rjj;


    TBranch        *bJetsPt=0;   //!
    TBranch        *bJetsEta=0;   //!
    TBranch        *bJetsPhi=0;   //!
    TBranch        *bJetsSameVertex_pt=0 ;
    TBranch        *bJetsSameVertex_eta=0;   
    TBranch        *bJetsSameVertex_phi=0;
    TBranch        *bCandidatesJets_pt=0;
    TBranch        *bCandidatesJets_eta=0;
    TBranch        *bCandidatesJets_phi=0;
    TBranch        *bVertexZPPS; 
    TBranch        *bnVertex;   //!
    TBranch        *bnTracks;   //!
    TBranch        *bMinDistance;   //!
    TBranch        *bMaxDistance;   //!
    TBranch        *bGoldenVertexZ;   //!
    TBranch        *bxiPPSArmB;   //!
    TBranch        *bxiPPSArmF;   //!
    TBranch        *btPPSArmB;   //!
    TBranch        *btPPSArmF;   //!
    TBranch        *bxPPSArmBDet1;   //!
    TBranch        *bxPPSArmFDet1;   //!
    TBranch        *byPPSArmBDet1;   //!
    TBranch        *byPPSArmFDet1;   //!
    TBranch        *bxPPSArmBDet2;   //!
    TBranch        *bxPPSArmFDet2;   //!
    TBranch        *byPPSArmBDet2;   //!
    TBranch        *byPPSArmFDet2;   //!
    TBranch        *bstopPPSArmFTrkDet1;   //!
    TBranch        *bstopPPSArmFTrkDet2;   //!
    TBranch        *bstopPPSArmBTrkDet1;   //!
    TBranch        *bstopPPSArmBTrkDet2;   //!
    TBranch        *bstopPPSArmFToF;   //!
    TBranch        *bstopPPSArmBToF;   //!
    TBranch        *bMjj;   //!
    TBranch        *bCandidatesMjj=0;
    TBranch        *bMpf;   //!
    TBranch        *bRjj;   //!

    tr->SetBranchAddress("JetsPt", &JetsPt, &bJetsPt);
    tr->SetBranchAddress("JetsEta", &JetsEta, &bJetsEta);
    tr->SetBranchAddress("JetsPhi", &JetsPhi, &bJetsPhi);
    tr->SetBranchAddress("JetsSameVertex_pt",&JetsSameVertex_pt,&bJetsSameVertex_pt);
    tr->SetBranchAddress("JetsSameVertex_eta",&JetsSameVertex_eta,&bJetsSameVertex_eta);
    tr->SetBranchAddress("JetsSameVertex_phi",&JetsSameVertex_phi,&bJetsSameVertex_phi);
    tr->SetBranchAddress("CandidatesJets_pt",&CandidatesJets_pt,&bCandidatesJets_pt);
    tr->SetBranchAddress("CandidatesJets_eta",&CandidatesJets_eta,&bCandidatesJets_eta);  
    tr->SetBranchAddress("CandidatesJets_phi",&CandidatesJets_phi,&bCandidatesJets_phi);  
    tr->SetBranchAddress("VertexZPPS", &VertexZPPS, &bVertexZPPS);
    tr->SetBranchAddress("nVertex", &nVertex, &bnVertex);
    tr->SetBranchAddress("nTracks", &nTracks, &bnTracks);
    tr->SetBranchAddress("MinDistance", &MinDistance, &bMinDistance);
    tr->SetBranchAddress("MaxDistance", &MaxDistance, &bMaxDistance);
    tr->SetBranchAddress("GoldenVertexZ", &GoldenVertexZ, &bGoldenVertexZ);
    tr->SetBranchAddress("xiPPSArmB", &xiPPSArmB, &bxiPPSArmB);
    tr->SetBranchAddress("xiPPSArmF", &xiPPSArmF, &bxiPPSArmF);
    tr->SetBranchAddress("tPPSArmB", &tPPSArmB, &btPPSArmB);
    tr->SetBranchAddress("tPPSArmF", &tPPSArmF, &btPPSArmF);
    tr->SetBranchAddress("xPPSArmBDet1", &xPPSArmBDet1, &bxPPSArmBDet1);
    tr->SetBranchAddress("xPPSArmFDet1", &xPPSArmFDet1, &bxPPSArmFDet1);
    tr->SetBranchAddress("yPPSArmBDet1", &yPPSArmBDet1, &byPPSArmBDet1);
    tr->SetBranchAddress("yPPSArmFDet1", &yPPSArmFDet1, &byPPSArmFDet1);
    tr->SetBranchAddress("xPPSArmBDet2", &xPPSArmBDet2, &bxPPSArmBDet2);
    tr->SetBranchAddress("xPPSArmFDet2", &xPPSArmFDet2, &bxPPSArmFDet2);
    tr->SetBranchAddress("yPPSArmBDet2", &yPPSArmBDet2, &byPPSArmBDet2);
    tr->SetBranchAddress("yPPSArmFDet2", &yPPSArmFDet2, &byPPSArmFDet2);
    tr->SetBranchAddress("stopPPSArmFTrkDet1", &stopPPSArmFTrkDet1, &bstopPPSArmFTrkDet1);
    tr->SetBranchAddress("stopPPSArmFTrkDet2", &stopPPSArmFTrkDet2, &bstopPPSArmFTrkDet2);
    tr->SetBranchAddress("stopPPSArmBTrkDet1", &stopPPSArmBTrkDet1, &bstopPPSArmBTrkDet1);
    tr->SetBranchAddress("stopPPSArmBTrkDet2", &stopPPSArmBTrkDet2, &bstopPPSArmBTrkDet2);
    tr->SetBranchAddress("stopPPSArmFToF", &stopPPSArmFToF, &bstopPPSArmFToF);
    tr->SetBranchAddress("stopPPSArmBToF", &stopPPSArmBToF, &bstopPPSArmBToF);
    tr->SetBranchAddress("CandidatesMjj",&CandidatesMjj,&bCandidatesMjj);  
    tr->SetBranchAddress("Mjj", &Mjj, &bMjj);
    tr->SetBranchAddress("Mpf", &Mpf, &bMpf);
    tr->SetBranchAddress("Rjj", &Rjj, &bRjj);
    //----------- settings ---------------
    bool verbose = false;
    int NEVENTS = tr->GetEntries();
    cout<<"MC EVENTS= "<<NEVENTS<<endl;
    float cross_section =1700.0 ; //[fb]
    float luminosity=100.0;//[fb]^-1
    double lumiweight = (luminosity*cross_section)/NEVENTS;
    cout<<"lumiweight= "<<lumiweight<<endl;
    double mclumiweight = 1.0;
    if (switchlumiweight ){
        mclumiweight = lumiweight;
    }

    int Njets=0;
    double pTmin  = 50.0;
    double etamin = -2.0;
    double etamax = 2.0;
    double MxPPS = -999.0;
    double MJJ = -999.0;
    double MxPPSBeforeCuts = 0.0;
    double MJJBC = -999.0;
    double deltaeta = 0.0;
    double deltaphi = 0.0;
    double S = 13000.0;
    double xmax = -3.15;
    double xmin =-23.15;
    double xmax2 = -2.03;
    double xmin2 = -22.03; 
    double ymax = 9.0;
    double ymin =-9.0;


    //--------- book histos ---------------------------------
    TH1F *hNJets = new TH1F("NJets","N Jets;  N Jets; N events",100,0,100);
    TH1F *hVertexZCMS = new TH1F("VertexZCMS"," Vertex Z CMS[cm];  Vertex Z [cm]; N events",25,-25.0,25.0);
    TH1F *hVertexZPPS = new TH1F("VertexZPPS","Vertex Z PPS [cm]; Vertex  Z [cm]; N events",25,-25.0,25.0);
    TH2F *hVertexZCMSPPS = new TH2F("VertexZCMSPPS","Vertex Z CMS vs Vertex Z  PPS; Vertex Z CMS [cm]; Vertex Z PPS [cm]",25,-25.0,25.0,25, -25.0,25.0);
    TH1F *hLeadingJetPt = new TH1F("LeadingJetPt","Leading Jet - P_{T} Distribution; P_{T} [GeV.c^{-1}]; N events",100,0,500);
    TH1F *hSecondJetPt = new TH1F("SecondJetPt","Second Jet - P_{T} Distribution; P_{T} [GeV.c^{-1}]; N events",100,0,500);
    TH1F *hLeadingJetEta = new TH1F("LeadingJetEta","Leading Jet - #eta Distribution; #eta; N events",100,-5.2,5.2);
    TH1F *hSecondJetEta = new TH1F("SecondJetEta","Second Jet - #eta Distribution; #eta; N events",100,-5.2,5.2);
    TH1F *hLeadingJetPhi = new TH1F("LeadingJetPhi","Leading Jet - #phi Distribution; #phi; N events",100,-1.2*PI,1.2*PI);
    TH1F *hSecondJetPhi = new TH1F("SecondJetPhi","Second Jet - #phi Distribution; #phi; N events",100,-1.2*PI,1.2*PI);  
    TH1F *hDeltaEtaJets = new TH1F("DeltaEtaJets","#Delta#eta_{jj} Distribution; #Delta#eta_{jj}; N events",20,0.0,5.2);
    TH1F *hDeltaPhiJets = new TH1F("DeltaPhiJets","#Delta#phi_{jj} Distribution; #Delta#phi_{jj}; N events",20,0.0,1.2*PI);
    TH1F *hMjj = new TH1F( "Mjj" , "Mass_{JJ} Distribution; M_{jj}  [GeV]; N events" , 100, 0., 2000. );
    TH1F *hMx = new TH1F("Mx" , "Mass_{X} Distribution; M_{x}  [GeV]; N events" , 100, 0., 2000. );
    TH1F *hMjjBC = new TH1F( "MjjBC" , "Mass_{JJ} Distribution; M_{jj}  [GeV]; N events" , 100, 0., 2000. );
    TH1F *hMxBC = new TH1F("MxBC" , "Mass_{X} Distribution; M_{x}  [GeV]; N events" , 100, 0., 2000. );
    TH1F *hPPS_xiARMPlus =  new TH1F( "PPS_xiARMPlus" , "#xi_{plus} PPS; #xi_{plus}; N Event" , 100, 0., 0.4 );
    TH1F *hPPS_xiARMMinus =  new TH1F( "PPS_xiARMMinus" , "#xi_{minus} PPS; #xi_{minus}; N Event" , 100, 0., 0.4 ); 
    TH2F *hPPS_xVsy_ARMPlusDt1 =  new TH2F( "PPS_xVsy_ARMPlusDt1" , "PPS x_vs_y_{ARMPlusDt1}; x [mm]; y [mm]" , 100, -50.0, 10.0,100,-10.0,10.0 ); 
    TH2F *hPPS_xVsy_ARMPlusDt2 =  new TH2F( "PPS_xVsy_ARMPlusDt2" , "PPS x_vs_y_{ARMPlusDt2}; x [mm]; y [mm]" , 100, -50.0, 10.0,100,-10.0,10.0 );  
    TH2F *hPPS_xVsy_ARMMinusDt1 =  new TH2F( "PPS_xVsy_ARMMinusDt1" , "PPS x_vs_y_{ARMMinusDt1}; x [mm]; y [mm]" , 100, -50.0, 10.0,100,-10.0,10.0 ); 
    TH2F *hPPS_xVsy_ARMMinusDt2 =  new TH2F( "PPS_xVsy_ARMMinusDt2" , "PPS x_vs_y_{ARMMinusDt2}; x [mm]; y [mm]" , 100, -50.0, 10.0,100,-10.0,10.0 ); 
    TH2F *hMxPPSvsMjj =  new TH2F("MxvsMjj" , "Mass_{X} vs M_{JJ}  Distribution; M_{x}  [GeV];  M_{jj}  [GeV]" , 100, 0., 2000.,100, 0., 2000. );
    TH2F *hMxPPSvsMjjBC =  new TH2F("MxvsMjjBC" , "Mass_{X} vs M_{JJ}  Distribution; M_{x}  [GeV];  M_{jj}  [GeV]" , 100, 0., 2000.,100, 0., 2000. );
    TH1F *hLeadingJetPtAfterPPS = new TH1F("LeadingJetPtAfterPPS","Leading Jet - P_{T} Distribution; P_{T} [GeV.c^{-1}]; N events",100,0,500);
    TH1F *hSecondJetPtAfterPPS = new TH1F("SecondJetPtAfterPPS","Second Jet - P_{T} Distribution; P_{T} [GeV.c^{-1}]; N events",100,0,500);
    TH1F *hLeadingJetEtaAfterPPS = new TH1F("LeadingJetEtaAfterPPS","Leading Jet - #eta Distribution; #eta; N events",100,-5.2,5.2);
    TH1F *hSecondJetEtaAfterPPS = new TH1F("SecondJetEtaAfterPPS","Second Jet - #eta Distribution; #eta; N events",100,-5.2,5.2);
    TH1F *hLeadingJetPhiAfterPPS = new TH1F("LeadingJetPhiAfterPPS","Leading Jet - #phi Distribution; #phi; N events",100,-1.2*PI,1.2*PI);  
    TH1F *hSecondJetPhiAfterPPS = new TH1F("SecondJetPhiAfterPPS","Second Jet - #phi Distribution; #phi; N events",100,-1.2*PI,1.2*PI);    
    TH1F *hDeltaEtaJetsAfterPPS = new TH1F("DeltaEtaJetsAfterPPS","#Delta#eta_{jj} Distribution; #Delta#eta_{jj}; N events",20,0.0,5.2);
    TH1F *hDeltaPhiJetsAfterPPS = new TH1F("DeltaPhiJetsAfterPPS","#Delta#phi_{jj} Distribution; #Delta#phi_{jj}; N events",20,0.0,1.2*PI);
    //----------- counters -----------------------
    int counter_jetpT(0),counter_jetEta(0), counter_fiducial(0), counter_hasStoped(0),counter_xiArms(0);
    //----------- tree reading -------------------
    unsigned NEntries = tr->GetEntries();
    cout<<"Reading TREE: "<<NEntries<<" events"<<endl;
    int decade = 0;
    for(unsigned i=0;i<NEVENTS;i++) {
        //----------- progress report -------------
        double progress = 10.0*i/(1.0*NEVENTS);
        //int k = TMath::FloorNint(progress);
        Int_t k = TMath::FloorNint(progress);
        if (k > decade) 
            cout<<10*k<<" %"<<endl;
        decade = k;          
        //----------- read the event --------------
        tr->GetEntry(i);
        Njets = CandidatesJets_pt->size();
        //hNJets->Fill(Njets);

        if (CandidatesJets_pt->size()<2)continue;
        if(verbose)cout<<"CandidatesJets_pt->size ="<<CandidatesJets_pt->size()<<endl;


        //------- fill some Jets  histograms ------------------
        hLeadingJetPt->Fill(CandidatesJets_pt->at(0),mclumiweight);
        hSecondJetPt->Fill(CandidatesJets_pt->at(1),mclumiweight);
        hLeadingJetEta->Fill(CandidatesJets_eta->at(0),mclumiweight);
        hSecondJetEta->Fill(CandidatesJets_eta->at(1),mclumiweight);
        hLeadingJetPhi->Fill(CandidatesJets_phi->at(0),mclumiweight);
        hSecondJetPhi->Fill(CandidatesJets_phi->at(1),mclumiweight);
        deltaeta = fabs(CandidatesJets_eta->at(0)-CandidatesJets_eta->at(1));
        deltaphi = fabs(CandidatesJets_phi->at(0)-CandidatesJets_phi->at(1));
        if (deltaphi> PI){deltaphi = 2.0*PI - deltaphi;}
        hDeltaEtaJets->Fill(deltaeta,mclumiweight);
        hDeltaPhiJets->Fill(deltaphi),mclumiweight;

        hVertexZCMSPPS->Fill(GoldenVertexZ,VertexZPPS,mclumiweight);        
        hVertexZCMS->Fill(GoldenVertexZ,mclumiweight);
        hVertexZPPS->Fill(VertexZPPS,mclumiweight);
        //--------- PPS x vs y -----------------------
        //x,det1 e det2 nos dois arms < - 3.1 e  > -23.1 mm
        //y,det1 e det2 nos dois arms > -9 e < 9 mm
        bool cutXArmF = ((xmin<xPPSArmFDet1 && xPPSArmFDet1<xmax) && (xmin2<xPPSArmFDet2 && xPPSArmFDet2<xmax2));
        bool cutXArmB = ((xmin<xPPSArmBDet1 && xPPSArmBDet1<xmax) && (xmin2<xPPSArmBDet2 && xPPSArmBDet2<xmax2));
        bool cutYArmF = ((ymin<yPPSArmFDet1 && yPPSArmFDet1<ymax) && (ymin<yPPSArmFDet2 && yPPSArmFDet2<ymax));
        bool cutYArmB = ((ymin<yPPSArmBDet1 && yPPSArmBDet1<ymax) && (ymin<yPPSArmBDet2 &&  yPPSArmBDet2<ymax));
        if(verbose)std::cout<<"XArmF:" <<cutXArmF<<"XArmB:"<<cutXArmB<<"YArmF: "<<cutXArmF<<"YArmB: "<<cutYArmB<<std::endl;
        //--------- PPS noHasStoped -----------------------
        bool stopTrkArmF = (stopPPSArmFTrkDet1==0 && stopPPSArmFTrkDet2==0);
        bool stopTrkArmB = (stopPPSArmBTrkDet1 ==0 && stopPPSArmBTrkDet2 ==0);
        if(verbose)cout<<"stopTrkArmF:"<<stopTrkArmF<<" , "<<"stopTrkArmB"<<stopTrkArmB<<endl;
        // Mjj and Mx before PPS sel
        if(xiPPSArmF>0.0 && xiPPSArmB>0.0){
            MxPPSBeforeCuts = S*sqrt(xiPPSArmF*xiPPSArmB); 
            if(verbose)cout<<"Mx BF = "<<S*sqrt(xiPPSArmF*xiPPSArmB)<<endl;
            MJJBC = CandidatesMjj;
        }
        hMxBC->Fill(MxPPSBeforeCuts,mclumiweight);
        hMjjBC->Fill(MJJBC,mclumiweight);                                                                                        
        hMxPPSvsMjjBC->Fill(MxPPS,MJJ,mclumiweight);
        //PPS sel
        if(cutXArmF && cutYArmF && cutXArmB && cutYArmB){
            ++counter_fiducial;
            if(verbose)cout<<"x: "<<xPPSArmFDet1<<", "<<xPPSArmBDet1<<", "<<xPPSArmBDet1<<", "<<xPPSArmBDet2<<endl;
            if(verbose)cout<<"y: "<<yPPSArmFDet1<<", "<<yPPSArmBDet1<<", "<<yPPSArmBDet1<<", "<<yPPSArmBDet2<<endl;  
            if(stopTrkArmF && stopTrkArmB){
                ++counter_hasStoped;
                hPPS_xVsy_ARMPlusDt1->Fill(xPPSArmFDet1,yPPSArmFDet1,mclumiweight);
                hPPS_xVsy_ARMPlusDt2->Fill(xPPSArmFDet2,yPPSArmFDet2,mclumiweight); 
                hPPS_xVsy_ARMMinusDt1->Fill(xPPSArmBDet1,yPPSArmBDet1,mclumiweight);
                hPPS_xVsy_ARMMinusDt2->Fill(xPPSArmBDet2,yPPSArmBDet2,mclumiweight);
                //--------- PPS xi ----------------------------
                if(xiPPSArmF>0.0 && xiPPSArmB>0.0){
                    ++counter_xiArms;
                    if(CandidatesJets_pt->at(0)>pTmin && CandidatesJets_pt->at(1)>pTmin){
                        ++counter_jetpT; 

                        if((CandidatesJets_eta->at(0)>etamin && CandidatesJets_eta->at(0)<etamax)&&(CandidatesJets_eta->at(1)>etamin && CandidatesJets_eta->at(1)<etamax)){
                            ++counter_jetEta;
                            hPPS_xiARMPlus->Fill(xiPPSArmF,mclumiweight);
                            hPPS_xiARMMinus->Fill(xiPPSArmB,mclumiweight);
                            MxPPS = S*sqrt(xiPPSArmF*xiPPSArmB);
                            if(verbose)std::cout<<"xiPPSArmF="<< xiPPSArmF<<","<<"xiPPSArmB="<<xiPPSArmB<<", "<<"S= "<<S<<std::endl;
                            if(verbose)std::cout<<"Mx = "<<S*sqrt(xiPPSArmF*xiPPSArmB)<<std::endl;
                            MJJ = CandidatesMjj; 
                            hLeadingJetPtAfterPPS->Fill(CandidatesJets_pt->at(0),mclumiweight);
                            hSecondJetPtAfterPPS->Fill(CandidatesJets_pt->at(1),mclumiweight);
                            hLeadingJetEtaAfterPPS->Fill(CandidatesJets_eta->at(0),mclumiweight);
                            hSecondJetEtaAfterPPS->Fill(CandidatesJets_eta->at(1),mclumiweight);
                            hLeadingJetPhiAfterPPS->Fill(CandidatesJets_phi->at(0),mclumiweight);
                            hSecondJetPhiAfterPPS->Fill(CandidatesJets_phi->at(1),mclumiweight);
                            hDeltaEtaJetsAfterPPS->Fill(deltaeta,mclumiweight);
                            hDeltaPhiJetsAfterPPS->Fill(deltaphi,mclumiweight);
                            //--------------------------------------------
                        } // xi cut
                        hMx->Fill(MxPPS,mclumiweight);
                        if(verbose)std::cout<<"Mx_b = "<<S*sqrt(xiPPSArmF*xiPPSArmB)<<std::endl;
                        hMjj->Fill(MJJ,mclumiweight); 
                        if(verbose)std::cout<<"Mjj = "<<CandidatesMjj<<" "<<"MJJ = "<<Mjj<<std::endl;
                        hMxPPSvsMjj->Fill(MxPPS,MJJ,mclumiweight);
                    } //stopTrk
                } //x,y cut
            }//eta jet cuts
        }  //jet pt cut

    }// tree loop
    //----------------- print out some information ---------------
    cout<<"Events read:                      "<<NEVENTS<<endl;
    cout<<"MC cross-section:                 "<<cross_section<<" [fb]"<<endl;
    cout<<"Luminosity:                       "<<luminosity<<" [fb]^-1"<<endl;
    cout<<"Weight:                           "<<mclumiweight<<endl;
    cout<<"Events read:                      "<<NEVENTS<<endl;
    cout<<"Events after fiducial:            "<<counter_fiducial<<endl; 
    cout<<"Events after hasStoped:           "<<counter_hasStoped<<endl; 
    cout<<"Events after XiArms>0:            "<<counter_xiArms<<endl; 
    cout<<"Events after jetpT<50GeV:         "<<counter_jetpT<<endl;                                                                                          
    cout<<"Events after jetEta<2.0:          "<<counter_jetEta<<endl; 
    cout << "\n----------------------------------------------------" << endl;
    cout << "Numbers Normalized" << endl;
    cout << "------------------------------------------------------" << endl;
    cout<<"Events read:                      "<<NEVENTS*mclumiweight<<endl; 
    cout<<"Events after hasStoped:           "<<counter_hasStoped*mclumiweight<<endl; 
    cout<<"Events after XiArms>0:            "<<counter_xiArms*mclumiweight<<endl; 
    cout<<"Events after jetpT<50GeV:         "<<counter_jetpT*mclumiweight<<endl;                                                                                          
    cout<<"Events after jetEta<2.0:          "<<counter_jetEta*mclumiweight<<endl; 
    
    //----------------- save the histos to the output file ------
    outf->Write();
}

