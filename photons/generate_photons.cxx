#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib> 
#include <ctime>

#include "TRandom3.h" 
#include "TMath.h" 
#include "TTree.h"
#include "TFile.h"
#include "TVector3.h"
#include "TStopwatch.h"

void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <parameters>\n"
              << "Parameters (all mandatory):\n"
              << "\t-dz_msk VALUE\tSpecify the Z coordinate (mm) of the mask\n"
              << "\t-dz_det VALUE\tSpecify the Z coordinate (mm)of the detector\n"
              << "\t-d_scn VALUE\tSpecify half the size (mm) of the (squared) scene\n"
              << "\t-d_det VALUE\tSpecify half the size (mm) of the (squared) detector\n"
              << "\t-n VALUE\tSpecify the number of photons to be generated\n"
              << "\t-out FILE\tSpecify the output root file\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 13)
	{
		show_usage(argv[0]);
		return 1;
	}

	auto dz_msk = 0.;
	auto dz_det = 0.;
	auto d_scn = 0.;
	auto d_det = 0.;

	auto n_ph = 0;

	auto ok_dz_msk = false;
	auto ok_dz_det = false;
	auto ok_d_scn = false;
	auto ok_d_det = false;
	auto ok_n_ph = false;
	auto ok_out = false;

	std::string ofname;

	for (auto i = 1; i < argc; ++i)
	{
		std::string arg = argv[i++];
		if (arg == "-dz_msk")
		{
			dz_msk = std::atof(argv[i]);
			ok_dz_msk = true;
		}
		else if (arg == "-dz_det")
		{
			dz_det = std::atof(argv[i]);
			ok_dz_det = true;
		}
		else if (arg == "-d_scn")
		{
			d_scn =  std::atof(argv[i]);
			ok_d_scn = true;
		}
		else if (arg == "-d_det")
		{
			d_det =  std::atof(argv[i]);
			ok_d_det = true;
		}
		else if (arg == "-n")
		{
			n_ph = std::atoi(argv[i]);
			ok_n_ph = true;
		}
		else if (arg == "-out")
		{
			ofname = argv[i];
			ok_out = true;
		}
		else
		{
			std::cerr << arg << ": UNKNOWN PARAMETER" << std::endl;
			show_usage(argv[0]);
			return 1;
		}
	}

	if(!(ok_dz_msk && ok_dz_det && ok_d_scn && ok_d_det && ok_n_ph && ok_out))
	{
		show_usage(argv[0]);
		return 1;
	}
	else
	{
    		std::cout << "Using parameters values:\n"
              << "\tdz_msk = " << std::setw(8) << dz_msk << "\t\t\tZ coordinate (mm) of the mask\n"
              << "\tdz_det = " << std::setw(8) << dz_det << "\t\t\tZ coordinate (mm)of the detector\n"
              << "\td_scn  = " << std::setw(8) << d_scn  << "\t\t\thalf size (mm) of the (squared) scene\n"
              << "\td_det  = " << std::setw(8) << d_det  << "\t\t\thalf size (mm) of the (squared) detector\n"
              << "\tn      = " << std::setw(8) << n_ph  << "\t\t\tnumber of photons to be generated\n"
              << "\tout    = " << std::setw(8) << ofname << "\t\t\toutput root file\n"
              << std::endl;
	}

	TFile fout(ofname.c_str(),"RECREATE");

	TRandom3 rand(time(NULL));
	TTree t("photons","photons");

	TVector3 p0;
	TVector3 p1;
	TVector3 p2;
	TVector3 m;

	auto p_p0 = &p0;
	auto p_p1 = &p1;
	auto p_p2 = &p2;
	auto p_m = &m;

	t.Branch("p0",&p_p0);
	t.Branch("p1",&p_p1);
	t.Branch("p2",&p_p2);
	t.Branch("m",&p_m);
	
	auto z = 0.;
	auto theta = 0.;

	const auto pi = TMath::Pi();

	auto counter = 0;

	TStopwatch sw;
	sw.Start();

	while(counter < n_ph)
 	{
		z = rand.Uniform(1.);
		theta = rand.Uniform(2 * pi);

		m.SetX(TMath::Cos(theta)/z);
		m.SetY(TMath::Sin(theta)/z);
		m.SetZ(1.);

		p0.SetX(rand.Uniform(-d_scn, d_scn));
		p0.SetY(rand.Uniform(-d_scn, d_scn));
		p0.SetZ(0.);

		if(TMath::Abs(p0.X() + m.X() * dz_det) <= d_det && TMath::Abs(p0.Y() + m.Y() * dz_det) <= d_det)
		{
			p1.SetX(p0.X() + m.X() * dz_msk);
			p1.SetY(p0.Y() + m.Y() * dz_msk);
			p1.SetZ(dz_msk);

			p2.SetX(p0.X() + m.X() * dz_det);
			p2.SetY(p0.Y() + m.Y() * dz_det);
			p2.SetZ(dz_det);

			t.Fill();
			counter++;
		}
	}

	sw.Stop();
	t.Write();
	fout.Close();

	std::cout << "Real time:\t" << sw.RealTime() << " sec." << std::endl;
	std::cout << "Cpu time:\t" << sw.CpuTime() << " sec." << std::endl; 

	return 0;
}
