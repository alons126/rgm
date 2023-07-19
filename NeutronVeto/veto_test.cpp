#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <vector>
#include <typeinfo>

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TStyle.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include "clas12reader.h"
#include "HipoChain.h"
#include "neutron-veto/veto_functions.h"

using namespace std;
using namespace clas12;
using namespace TMVA;

const double c = 29.9792458;
const double mN = 0.939;
const double mP = 0.938;
const double mD = 1.8756;

void printProgress(double percentage);

void Usage()
{
  std::cerr << "Usage: ./code <MC =1,Data = 0> <Ebeam(GeV)> <path/to/ouput.root> <path/to/ouput.pdf> <path/to/input.hipo> \n";
}


int main(int argc, char ** argv)
{

  if(argc < 6)
    {
      std::cerr<<"Wrong number of arguments.\n";
      Usage();
      return -1;
    }

  /////////////////////////////////////
  
  bool isMC = false;
  if(atoi(argv[1]) == 1){isMC=true;}

  double Ebeam = atof(argv[2]);
  
  TFile * outFile = new TFile(argv[3],"RECREATE");
  char * pdfFile = argv[4];

  clas12root::HipoChain chain;
  for(int k = 5; k < argc; k++){
    cout<<"Input file "<<argv[k]<<endl;
    chain.Add(argv[k]);
  }
  auto config_c12=chain.GetC12Reader();
  chain.SetReaderTags({0});




  const std::unique_ptr<clas12::clas12reader>& c12=chain.C12ref();
  chain.db()->turnOffQADB();
  

  /////////////////////////////////////
  //Prepare histograms
  /////////////////////////////////////
  vector<TH1*> hist_list_1;
  vector<TH2*> hist_list_2;

  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleYSize(0.05);

  gStyle->SetTitleXOffset(0.8);
  gStyle->SetTitleYOffset(0.8);

  char temp_name[100];
  char temp_title[100];

  /////////////////////////////////////
  //Electron fiducials
  /////////////////////////////////////
  TH2D * h_phi_theta = new TH2D("phi_theta","#phi_{e} vs. #theta_{e} ;#phi_{e};#theta_{e}",100,-180,180,100,5,40);
  hist_list_2.push_back(h_phi_theta);



  /////////////////////////////////////
  //Electron Pid and Vertex
  /////////////////////////////////////
  TH1D * h_nphe = new TH1D("nphe","#Photo-electrons in HTCC;#Photo-electrons;Counts",40,0,40);
  hist_list_1.push_back(h_nphe);

  TH1D * h_vtz_e = new TH1D("vtz_e","Electron Z Vertex;vertex;Counts",100,-10,10);
  hist_list_1.push_back(h_vtz_e);


  
  /////////////////////////////////////
  //Electron Kinematics  
  /////////////////////////////////////
  TH1D * h_xB = new TH1D("xB","x_{B};x_{B};Counts",100,0,2);
  hist_list_1.push_back(h_xB);
  TH1D * h_QSq = new TH1D("QSq","Q^{2};Q^{2};Counts",100,0,3);
  hist_list_1.push_back(h_QSq);
  TH1D * h_WSq = new TH1D("WSq","W^{2};W^{2}",100,0,7);
  hist_list_1.push_back(h_WSq);
  TH2D * h_xB_QSq = new TH2D("xB_QSq","x_{B} vs. Q^{2} ;x_{B};Q^{2}",100,0,2,100,0,3);
  hist_list_2.push_back(h_xB_QSq);
  TH2D * h_xB_WSq = new TH2D("xB_WSq","x_{B} vs. W^{2} ;x_{B};W^{2}",100,0,2,100,0,7);
  hist_list_2.push_back(h_xB_WSq);
  TH2D * h_QSq_WSq = new TH2D("QSq_WSq","Q^{2} vs. W^{2} ;Q^{2};W^{2}",100,0,3,100,0,7);
  hist_list_2.push_back(h_QSq_WSq);

  TH2D * h_mom_theta[6];
  for(int i=0; i<6; i++){
    sprintf(temp_name,"mom_theta_%d",i+1);
    sprintf(temp_title,"p_{e} vs. #theta_{e} Sector=%d;Momentum;Theta",i+1);
    h_mom_theta[i] = new TH2D(temp_name,temp_title,100,0,7,100,5,40);
    hist_list_2.push_back(h_mom_theta[i]);
  }


  /////////////////////////////////////
  //CND Neutron Information
  /////////////////////////////////////
  TH2D * h_nsize_CND = new TH2D("nsize_CND","Number of Neutrons in CND;Number of Neutrons;Neutrons with Valid Momentum",10,0,10,10,0,10);
  hist_list_2.push_back(h_nsize_CND);



  TH1D * h_theta_n_CND = new TH1D("theta_n_CND","#theta_{neutron};#theta_{neutron};Counts",100,20,140);
  hist_list_1.push_back(h_theta_n_CND);
  TH2D * h_phi_theta_n_CND = new TH2D("phi_theta_n_CND","#phi_{n} vs. #theta_{n} ;#phi_{n};#theta_{n}",48,-180,180,100,35,145);
  hist_list_2.push_back(h_phi_theta_n_CND);
  TH2D * h_mom_beta_n_CND = new TH2D("mom_beta_n_CND","p_{n} vs. #beta_{n} ;p_{n};#beta_{n}",100,0.1,2,100,0.1,1);
  hist_list_2.push_back(h_mom_beta_n_CND);

  TH2D * h_mom_theta_n_CND = new TH2D("mom_theta_n_CND","p_{n} vs. #theta_{n} ;p_{n};#theta_{n}",100,0.2,1.5,100,35,145);
  hist_list_2.push_back(h_mom_theta_n_CND);
  TH2D * h_phi_mom_n_CND = new TH2D("phi_mom_n_CND","#phi_{n} vs p_{n};#phi_{n};p_{n}",48,-180,180,100,0.2,1.5);
  hist_list_2.push_back(h_phi_mom_n_CND);





  /////////////////////////////////////
  //CND Neutron Signal
  /////////////////////////////////////
  TH2D * h_pn_angles_sig = new TH2D("pn_angles_sig","Angular Separation between Proton and Neutron (Signal);#Delta#phi = #phi_{p} - #phi_{n};#Delta#theta = #theta_{p} - #theta_{n}",360,-180,180,360,-180,180);
  hist_list_2.push_back(h_pn_angles_sig);
  TH2D * h_n_thetaphi_sig = new TH2D("n_thetaphi_sig","Angular Distribution of Neutrons (Signal);#phi (deg);#theta (deg)",48,-180,180,100,40,140);
  hist_list_2.push_back(h_n_thetaphi_sig);
  TH2D * h_pn_pmiss_sig = new TH2D("pn_pmiss_sig","Neutron Measured Momentum vs Predicted Momentum (Signal);Neutron Predicted Momentum (GeV/c);Neutron Momentum (GeV/c)",100,0,1.2,100,0,1.2);
  hist_list_2.push_back(h_pn_pmiss_sig);
  TH1D * h_cos0_sig = new TH1D("cos0_sig","Angle between p_{n} and p_{miss} (Signal);cos #theta_{pn,pmiss};Counts",20,-1.1,1.1);
  hist_list_1.push_back(h_cos0_sig);
  TH1D * h_tof_sig = new TH1D("tof_sig","Time-of-Flight (Signal);TOF;Counts",100,-20,80);
  hist_list_1.push_back(h_tof_sig);
  TH1D * h_mom_sig = new TH1D("mom_sig","Measured Neutron Momentum (Signal);Momentum (GeV/c);Counts",100,0,1.5);
  hist_list_1.push_back(h_mom_sig);

  /////////////////////////////////////
  //CND Neutron Background
  /////////////////////////////////////
  TH2D * h_pn_angles_back = new TH2D("pn_angles_back","Angular Separation between Proton and Neutron (Background);#Delta#phi = #phi_{p} - #phi_{n};#Delta#theta = #theta_{p} - #theta_{n}",360,-180,180,360,-180,180);
  hist_list_2.push_back(h_pn_angles_back);
  TH2D * h_n_thetaphi_back = new TH2D("n_thetaphi_back","Angular Distribution of Neutrons (Background);#phi (deg);#theta (deg)",48,-180,180,100,40,140);
  hist_list_2.push_back(h_n_thetaphi_back);
  TH2D * h_pn_pmiss_back = new TH2D("pn_pmiss_back","Neutron Measured Momentum vs Predicted Momentum (Background);Neutron Predicted Momentum (GeV/c);Neutron Momentum (GeV/c)",100,0,1.2,100,0,1.2);
  hist_list_2.push_back(h_pn_pmiss_back);
  TH1D * h_cos0_back = new TH1D("cos0_back","Angle between p_{n} and p_{miss} (Background);cos #theta_{pn,pmiss};Counts",20,-1.1,1.1);
  hist_list_1.push_back(h_cos0_back);
  TH1D * h_tof_back = new TH1D("tof_back","Time-of-Flight (Signal);TOF;Counts",100,-20,80);
  hist_list_1.push_back(h_tof_back);
  TH1D * h_mom_back = new TH1D("mom_back","Measured Neutron Momentum (Signal);Momentum (GeV/c);Counts",100,0,1.5);
  hist_list_1.push_back(h_mom_back);


  /////////////////////////////////////
  //Signal and Background Histograms
  /////////////////////////////////////
  



  for(int i=0; i<hist_list_1.size(); i++){
    hist_list_1[i]->Sumw2();
    hist_list_1[i]->GetXaxis()->CenterTitle();
    hist_list_1[i]->GetYaxis()->CenterTitle();
  }
  for(int i=0; i<hist_list_2.size(); i++){
    hist_list_2[i]->Sumw2();
    hist_list_2[i]->GetXaxis()->CenterTitle();
    hist_list_2[i]->GetYaxis()->CenterTitle();
  }


  int counter = 0;


  // TMVA stuff
  //TMVA::Tools::Instance();
  TMVA::Reader * reader = new TMVA::Reader("!Color:!Silent");
  // define features for ML model
  Float_t energy, cnd_energy, ctof_energy, angle_diff, momentum;
  Float_t layermult, size, cnd_hits, ctof_hits;
  reader->AddVariable("energy", &energy);
  reader->AddVariable("layermult", &layermult);
  reader->AddVariable("size", &size);
  reader->AddVariable("cnd_hits", &cnd_hits);
  reader->AddVariable("cnd_energy", &cnd_energy);
  reader->AddVariable("ctof_energy", &ctof_energy);
  reader->AddVariable("ctof_hits", &ctof_hits);
  reader->AddVariable("angle_diff", &angle_diff);
  // spectator variable(s)
  reader->AddSpectator("momentum", &momentum);

  reader->BookMVA("BDT", "/w/hallb-scshelf2102/clas/clase2/erins/repos/rgm/NeutronVeto/dataset/weights/TMVAClassification_BDT.weights.xml");


  //Define cut class
  while(chain.Next()==true){
      //Display completed  
      counter++;
      if((counter%1000000) == 0){
	cerr << "\n" <<counter/1000000 <<" million completed";
      }    
      if((counter%100000) == 0){
	cerr << ".";
      }    

      // get particles by type
      auto allParticles = c12->getDetParticles();
      auto electrons=c12->getByID(11);
      auto protons=c12->getByID(2212);
      auto neutrons=c12->getByID(2112);
      double weight = 1;
      if(isMC){weight=c12->mcevent()->getWeight();}
      TVector3 	p_b(0,0,Ebeam);
      if(electrons.size()!=1){ continue;}

      double starttime = c12->event()->getStartTime();


  /////////////////////////////////////
  //Electron Kinematics  
  /////////////////////////////////////
      TVector3 p_e;
      p_e.SetMagThetaPhi(electrons[0]->getP(),electrons[0]->getTheta(),electrons[0]->getPhi());
      double EoP_e =  (electrons[0]->cal(PCAL)->getEnergy() +  electrons[0]->cal(ECIN)->getEnergy() +  electrons[0]->cal(ECOUT)->getEnergy()) / p_e.Mag();
      int nphe = electrons[0]->che(HTCC)->getNphe();
      double vtz_e = electrons[0]->par()->getVz(); 
      h_phi_theta->Fill(p_e.Phi()*180/M_PI,p_e.Theta()*180/M_PI,weight);
      if(EoP_e<=0){ continue; }
      h_nphe->Fill(nphe,weight);
      h_vtz_e->Fill(vtz_e,weight);


      TVector3	p_q = p_b - p_e;
      double theta_q =  p_q.Theta() * 180 / M_PI;
      double nu = Ebeam - p_e.Mag();
      double QSq = p_q.Mag2() - (nu*nu);
      double xB = QSq / (2 * mN * nu);
      double WSq = (mN*mN) - QSq + (2*nu*mN);
      double theta_e = p_e.Theta() * 180 / M_PI;
      //if(WSq>1.25){continue;}

      h_xB->Fill(xB,weight);
      h_QSq->Fill(QSq,weight);
      h_WSq->Fill(WSq,weight);
      h_xB_QSq->Fill(xB,QSq,weight);
      h_xB_WSq->Fill(xB,WSq,weight);
      h_QSq_WSq->Fill(QSq,WSq,weight);


  /////////////////////////////////////
  //Proton Kinematics  
  /////////////////////////////////////
      TVector3 p_p(0.,0.,0.);
      int p_index = -1;
      for (int i=0; i<protons.size(); i++)
      {
        p_p.SetMagThetaPhi(protons[i]->getP(),protons[i]->getTheta(),protons[i]->getPhi());
        double dbeta = protons[i]->par()->getBeta() - p_p.Mag()/sqrt(p_p.Mag2()+mP*mP);
        double vzp = protons[i]->par()->getVz();
        double chipid = protons[i]->par()->getChi2Pid();
        if ((vzp-vtz_e)<-4. || (vzp-vtz_e)>4.) {continue;}
        if (chipid<-3. || chipid>3.) {continue;}
        if (dbeta<-0.05 || dbeta>0.05) {continue;}
        // require proton to be in correct angle and momentum range for the requested detector
        double p_theta = p_p.Theta()*180./M_PI;
        // forward proton
        if (p_theta>40 || (p_p.Mag()<0.5 || p_p.Mag()>3.0)) {continue;}
        // central proton
        //if ((p_theta<40 || p_theta>140) || (p_p.Mag()<0.2 || p_p.Mag()>1.2)) {continue;}
        p_index = i;
      }
      
      if (p_index<0) {continue;}
      p_p.SetMagThetaPhi(protons[p_index]->getP(),protons[p_index]->getTheta(),protons[p_index]->getPhi());



  /////////////////////////////////////
  //Missing Momentum 
  /////////////////////////////////////
      TVector3 p_pred = p_q - p_p;
      /*if (p_pred.Mag()<0.2 || p_pred.Mag()>1.2) {continue;}
      if (p_pred.Theta()*180./M_PI<40 || p_pred.Theta()*180./M_PI>135) {continue;}
      double Ep = sqrt(mN*mN + p_p.Mag2());
      double Emiss = Ebeam + mD - p_e.Mag() - Ep;
      double mmiss = sqrt((Emiss*Emiss) - p_pred.Mag2());
      if (mmiss<0.7 || mmiss>1.05) {continue;}*/


  /////////////////////////////////////
  //CND Neutron Information
  /////////////////////////////////////
      int nn_CND = 0; int nn_CND_good = 0;

      for(int j = 0; j < neutrons.size(); j++){
	TVector3 p_n;
	p_n.SetMagThetaPhi(neutrons[j]->getP(),neutrons[j]->getTheta(),neutrons[j]->getPhi());
	double E_n = sqrt(mN*mN + p_n.Mag2());
	double theta_n = p_n.Theta() * 180 / M_PI;
	double phi_n = p_n.Phi() * 180 / M_PI;
	double theta_nq = p_n.Angle(p_q) * 180 / M_PI;
	double beta_n = neutrons[j]->par()->getBeta();
	//double phi_diff = get_phi_diff(p_e,p_n);
	double cos0 = p_pred.Dot(p_n) / (p_pred.Mag()*p_n.Mag());

	double path_n = neutrons[j]->getPath();
	double beta_frommom_n = p_n.Mag()/E_n;
	double time_frommom_n = path_n / (c*beta_frommom_n);
	double time_frombeta_n = path_n / (c*beta_n);

        bool CND1 = (neutrons[j]->sci(clas12::CND1)->getDetector() == 3);
        bool CND2 = (neutrons[j]->sci(clas12::CND2)->getDetector() == 3);
        bool CND3 = (neutrons[j]->sci(clas12::CND3)->getDetector() == 3);
        bool CND = CND1 || CND2 || CND3;
        bool CTOF = (neutrons[j]->sci(clas12::CTOF)->getDetector() == 4);

/*        double Edep = 0; double tof = 0;
//std::cout << CND1 << '\t' << CND2 << '\t' << CND3 << '\t' << CTOF << '\n';
        if (CND1){
          Edep = neutrons[j]->sci(CND1)->getEnergy();
          tof = neutrons[j]->sci(CND1)->getTime();// - starttime;
        }
        else if (CND2){
          Edep = neutrons[j]->sci(CND2)->getEnergy();
          tof = neutrons[j]->sci(CND2)->getTime();// - starttime;
        }
        else if (CND3){
          Edep = neutrons[j]->sci(CND3)->getEnergy();
          tof = neutrons[j]->sci(CND3)->getTime();// - starttime;
        }
        else if (CTOF){
          Edep = neutrons[j]->sci(CTOF)->getEnergy();
          tof = neutrons[j]->sci(CTOF)->getTime();// - starttime;
        } // returns 0???*/

//std::cout << tof << '\n';
//std::cout << Edep << '\n';
        //if (Edep<3) {continue;}

        if (!CND) {continue;}

        nn_CND += 1;

        // cut out obviously bad neutrons
        if (beta_frommom_n==0) {continue;}
        if (theta_n==0) {continue;}
        if (phi_n==0) {continue;}
        if (p_n.Mag()<0.25) {continue;}

        // good neutron candidates start here
        if (theta_n<40 || theta_n>140) {continue;}
        if (p_n.Mag()<0.25 || p_n.Mag()>1.2) {continue;}

        nn_CND_good += 1;

	h_theta_n_CND->Fill(theta_n,weight);
        h_phi_theta_n_CND->Fill(phi_n,theta_n,weight);
	h_mom_beta_n_CND->Fill(p_n.Mag(),beta_n,weight);
	h_mom_theta_n_CND->Fill(p_n.Mag(),theta_n,weight);
        h_phi_mom_n_CND->Fill(phi_n,p_n.Mag(),weight);


          
        // fill histos with CND::hits bank info

        // extra bank info
        double dedx = neutrons[j]->sci(clas12::CND1)->getDedx() + neutrons[j]->sci(clas12::CND2)->getDedx() + neutrons[j]->sci(clas12::CND3)->getDedx();
        double csize = neutrons[j]->sci(clas12::CND1)->getSize() + neutrons[j]->sci(clas12::CND2)->getSize() + neutrons[j]->sci(clas12::CND3)->getSize();
        double layermult = neutrons[j]->sci(clas12::CND1)->getLayermulti() + neutrons[j]->sci(clas12::CND2)->getLayermulti() + neutrons[j]->sci(clas12::CND3)->getLayermulti();




        // TEST ML HERE
        // get neutron features
        Struct ninfo = getFeatures(neutrons, allParticles, j);
        cnd_hits = ninfo.cnd_hits;
        cnd_energy = ninfo.cnd_energy;
        ctof_hits = ninfo.ctof_hits;
        ctof_energy = ninfo.ctof_energy;
        layermult = ninfo.layermult;
        energy = ninfo.energy;
        size = ninfo.size;
        angle_diff = ninfo.angle_diff;
        // spectator
        momentum = p_n.Mag();
        
        // apply ML model
        double mvaValue = reader->EvaluateMVA("BDT");

        // BDT: signal cut>0.1, background cut<0.1
        // MLP: signal cut>0.5, background<0.5

        if (mvaValue>0.1) // signal
        {
          h_pn_angles_sig->Fill(p_p.Phi()*180./M_PI-p_n.Phi()*180./M_PI, p_p.Theta()*180./M_PI-p_n.Theta()*180./M_PI, weight);
          h_pn_pmiss_sig->Fill(p_pred.Mag(),p_n.Mag(),weight);
          h_cos0_sig->Fill(cos0,weight);
          h_n_thetaphi_sig->Fill(p_n.Phi()*180./M_PI, p_n.Theta()*180./M_PI, weight);
          //h_tof_sig->Fill(tof,weight);
          h_mom_sig->Fill(p_n.Mag(),weight);
        }
        else // background
        {
          h_pn_angles_back->Fill(p_p.Phi()*180./M_PI-p_n.Phi()*180./M_PI, p_p.Theta()*180./M_PI-p_n.Theta()*180./M_PI, weight);
          h_pn_pmiss_back->Fill(p_pred.Mag(),p_n.Mag(),weight);
          h_cos0_back->Fill(cos0,weight);
          h_n_thetaphi_back->Fill(p_n.Phi()*180./M_PI, p_n.Theta()*180./M_PI, weight);
          //h_tof_back->Fill(tof,weight);
          h_mom_back->Fill(p_n.Mag(),weight);
        }


      }

      h_nsize_CND->Fill(nn_CND,nn_CND_good,weight);



/*

  /////////////////////////////////////
  //Compare CND Neutrons to Pmiss
  /////////////////////////////////////

  // only events with 1 proton and 1 neutron
  if (protons.size()!=1) {continue;}
  if (neutrons.size()!=1) {continue;}

  // skip events with particles other than proton, neutrons, electron, photon
  bool trash = 0;
  for(int j = 0; j < allParticles.size(); j ++){
    int PID = allParticles[j]->getPid();
    if (PID!=2212 && PID!=2112 && PID!=22 && PID!=11){
      trash = 1;
    }
  }
  if (trash) {continue;}

  TVector3 p_p;
  p_p.SetMagThetaPhi(protons[0]->getP(),protons[0]->getTheta(),protons[0]->getPhi());
  TVector3 p_pred = p_p - p_q;
  double theta_pm = p_pred.Theta()*180 / M_PI;


  for(int j = 0; j < neutrons.size(); j++){
	TVector3 p_n;
	p_n.SetMagThetaPhi(neutrons[j]->getP(),neutrons[j]->getTheta(),neutrons[j]->getPhi());
	double E_n = sqrt(mN*mN + p_n.Mag2());
	double theta_n = p_n.Theta() * 180 / M_PI;
	double phi_n = p_n.Phi() * 180 / M_PI;
	double beta_frommom_n = p_n.Mag()/E_n;
        double cos0 = p_pred.Dot(p_n) / (p_pred.Mag()*p_n.Mag());

        double dphi_pn = protons[0]->getPhi()*180./M_PI - phi_n;
        double dtheta_pn = protons[0]->getTheta()*180./M_PI - theta_n;

        bool CND1 = (neutrons[j]->sci(clas12::CND1)->getDetector() == 3);
        bool CND2 = (neutrons[j]->sci(clas12::CND2)->getDetector() == 3);
        bool CND3 = (neutrons[j]->sci(clas12::CND3)->getDetector() == 3);

        // cuts to get good neutrons
        if (beta_frommom_n==0) {continue;}
        if (theta_n==0) {continue;}
        if (phi_n==0) {continue;}
        if (p_n.Mag()<0.2) {continue;}
        if (theta_n<40 || theta_n>140) {continue;}

        // require pmiss to be as expected
        if (p_pred.Mag()<0.2) {continue;}
        if (theta_pm<40 || theta_pm>140) {continue;}

        // "good neutrons" start here
        if(CND){
          h_pn_angles->Fill( dphi_pn , dtheta_pn , weight);
          if (dtheta_pn>-15) {continue;}
          h_pn_pmiss->Fill(p_pred.Mag(),p_n.Mag(),weight);
          h_cos0->Fill(cos0,weight);
          h_theta_phi_p->Fill(p_p.Theta()*180./M_PI,p_p.Phi()*180./M_PI,weight);
        }

  }
*/
  
  }

  cout<<counter<<endl;

  outFile->cd();
  for(int i=0; i<hist_list_1.size(); i++){
    hist_list_1[i]->Write();
  }
  for(int i=0; i<hist_list_2.size(); i++){
    hist_list_2[i]->Write();
  }


  /////////////////////////////////////////////////////
  //Now create the output PDFs
  /////////////////////////////////////////////////////
  int pixelx = 1980;
  int pixely = 1530;
  TCanvas * myCanvas = new TCanvas("myPage","myPage",pixelx,pixely);
  TCanvas * myText = new TCanvas("myText","myText",pixelx,pixely);
  TLatex text;
  text.SetTextSize(0.05);

  char fileName[100];
  sprintf(fileName,"%s[",pdfFile);
  myText->SaveAs(fileName);
  sprintf(fileName,"%s",pdfFile);



  /////////////////////////////////////
  //Electron Kinematics  
  /////////////////////////////////////
  myText->cd();
  text.DrawLatex(0.2,0.9,"(e,e') Cuts:");
  double line = 0.8;

  myText->Print(fileName,"pdf");  
  myText->Clear();
  
  myCanvas->Divide(2,3);
  myCanvas->cd(1);
  h_xB->Draw();
  myCanvas->cd(2);
  h_QSq->Draw();
  myCanvas->cd(3);
  h_WSq->Draw();
  myCanvas->cd(4);
  h_xB_QSq->Draw("colz");
  myCanvas->cd(5);
  h_xB_WSq->Draw("colz");
  myCanvas->cd(6);
  h_QSq_WSq->Draw("colz");
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();
  

  /////////////////////////////////////
  //CND Neutron Information
  /////////////////////////////////////
  myText->cd();
  text.DrawLatex(0.2,0.9,"(e,e'n) Cuts:");
  text.DrawLatex(0.2,0.8,"(e,e') Cuts");
  text.DrawLatex(0.2,0.7,"Neutron Detected in CND");
  text.DrawLatex(0.2,0.6,"Neutron #beta, #theta, #phi, p all nonzero");
  text.DrawLatex(0.2,0.5,"Neutron #theta: min=40 deg, max=140 deg");
  myText->Print(fileName,"pdf");
  myText->Clear();

  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_nsize_CND->Draw("colz");
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();

  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_theta_n_CND->Draw();
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();

  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_phi_theta_n_CND->Draw("colz");
  myCanvas->cd(2);
  h_mom_theta_n_CND->Draw("colz");
  myCanvas->cd(3);
  h_phi_mom_n_CND->Draw("colz");
  myCanvas->cd(4);
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();





  /////////////////////////////////////
  //CND Neutron Signald & Background
  /////////////////////////////////////
  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_n_thetaphi_sig->Draw("colz");
  myCanvas->cd(2);
  h_n_thetaphi_back->Draw("colz");
  myCanvas->cd(3);
  h_pn_angles_sig->Draw("colz");
  myCanvas->cd(4);
  h_pn_angles_back->Draw("colz");
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();

  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_pn_pmiss_sig->Draw("colz");
  myCanvas->cd(2);
  h_pn_pmiss_back->Draw("colz");
  myCanvas->cd(3);
  h_cos0_sig->Draw();
  h_cos0_sig->SetStats(0);
  myCanvas->cd(4);
  h_cos0_back->Draw();
  h_cos0_back->SetStats(0);
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();

  myCanvas->Divide(2,2);
  myCanvas->cd(1);
  h_tof_sig->Draw();
  myCanvas->cd(2);
  h_tof_back->Draw();
  myCanvas->cd(3);
  h_mom_sig->Draw();
  myCanvas->cd(4);
  h_mom_back->Draw();
  myCanvas->Print(fileName,"pdf");
  myCanvas->Clear();



  sprintf(fileName,"%s]",pdfFile);
  myCanvas->Print(fileName,"pdf");

  outFile->Close();
}


void printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}
