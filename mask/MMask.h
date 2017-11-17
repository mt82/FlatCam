#ifndef MMASK_H
#define MMASK_H

#include <TH2C.h>
#include <TMatrixD.h>
#include <TVector3.h>
#include <TVectorD.h>

#include <iostream>
#include <map>
#include <vector>



//-------------------------------------
class MMLS : public TObject {
private:
	std::vector<int> m_seq;
	int m_nreg;
	int m_idLSFR;
	static std::map<int, std::vector<int>*>* m_LSFR;
	static bool m_isinit;

	void Init();
	void Build();
public:
	MMLS() : m_seq(), m_nreg(8), m_idLSFR(12) { Init();};
	MMLS(int n, int id) : m_seq(), m_nreg(n), m_idLSFR(id) { Init();};
	void SetIdLFSR(int id) {m_idLSFR = id;};
	int GetLFSR() const {return m_LSFR->at(m_nreg)->at(m_idLSFR);};
	void SetNReg(int n) {m_nreg = n;};
	int GetNReg() const {return m_nreg;};
	std::vector<int> GetSeq() {Build(); return m_seq;};
	TH1I& GetHisto();

ClassDef(MMLS,1);
};

//-------------------------------------
class MCode : public TObject {
private:
	int m_nrepV;
	int m_nrepH;
	TMatrixD m_mtx;
public:
	MCode() : m_nrepV(1), m_nrepH(1), m_mtx(1,1) {;};
	MCode(std::vector<int> w_ver, std::vector<int> w_hor, int n_ver, int n_hor);
	MCode(TMatrixD mtx, int n_ver, int n_hor);
	MCode(MCode& code);
	~MCode() {;};
	const TMatrixD& GetMtxCode() const {return m_mtx;};
	int GetNHorRep() const {return m_nrepH;};
	int GetNVerRep() const {return m_nrepV;};

ClassDef(MCode,1);
};

//-------------------------------------
class MMask : public TObject {
private:
	double m_height;
	double m_width;
	TVector3 m_center;
	TMatrixD m_mtx;
	TH2C m_histo;

	void BuildHisto();
public:
	MMask() : m_height(1), m_width(1), m_center(0,0,0), m_mtx(1,1) , m_histo("","",m_mtx.GetNcols(), m_center.X() - 0.5 * m_width, m_center.X() + 0.5 * m_width, m_mtx.GetNrows(), m_center.Y() - 0.5 * m_height, m_center.Y() + 0.5 * m_height) {BuildHisto();};
	MMask(TMatrixD mtx, double x, double y, double z, double h, double w) : m_height(h), m_width(w), m_center(x,y,z), m_mtx(mtx) , m_histo("","",m_mtx.GetNcols(), m_center.X() - 0.5 * m_width, m_center.X() + 0.5 * m_width, m_mtx.GetNrows(), m_center.Y() - 0.5 * m_height, m_center.Y() + 0.5 * m_height) {BuildHisto();};
	MMask(MMask& msk) : m_height(msk.m_height), m_width(msk.m_width), m_center(msk.m_center), m_mtx(msk.m_mtx) , m_histo(msk.m_histo) {;};
	~MMask() {;};
	void Draw();
	const TMatrixD& GetMtx() const {return m_mtx;};
	const TH2C& GetHisto() const {return m_histo;}
	double X() const {return m_center.X();};
	double Y() const {return m_center.Y();};
	double Z() const {return m_center.Z();};
	double H() const {return m_height;};
	double W() const {return m_width;};
	bool Is_Transparet(double x, double y);

ClassDef(MMask,1);
};

#endif
