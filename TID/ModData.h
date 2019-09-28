#pragma once
#include "XhLdsLm.h"
#include "ldsptr_list.h"
#include "ArrayList.h"
#include "HashTable.h"
#include "XhCharString.h"
#include "SolidBody.h"
#include "LogFile.h"

class CModNode;
class CModRod;
typedef CTmaPtrList<CModNode,CModNode*> NODESET;
typedef CTmaPtrList<CModRod,CModRod*> RODSET;
//
class CModModel;
class CModHeightGroup;
class CModNode
{
	CModModel* m_pBelongModel;
public:
	char m_sLayer[4];
	CFGWORD cfgword;
	long point_i;
	f3dPoint xOrg;
public:	
	CModNode();
	//
	CModModel* BelongModel(){return m_pBelongModel;}
	void SetBelongModel(CModModel* pModel){m_pBelongModel=pModel;}
	void SetKey(DWORD key){point_i=key;}
	BOOL IsLegNode(){return m_sLayer[0]=='L';}
	BYTE GetLegQuad();
};
class CModRod
{
	BOOL Create3dJgSolidModel(CSolidBody *pSolidBody,BOOL bToLds=TRUE);
	BOOL Create3dTubeSolidModel(CSolidBody *pSolidBody,BOOL bToLds=TRUE);
	CModModel* m_pBelongModel;
public:
	long handle;
	BYTE m_ciRodType;	//1.�Ǹ�|2.�ֹ�
	char m_sLayer[4];
	CFGWORD cfgword;
	char m_cMaterial;
	double m_fWidth;
	double m_fThick;
	UINT m_uiNodeS,m_uiNodeE;
	f3dPoint m_vNormX,m_vNormY;
	f3dPoint m_vWingX,m_vWingY;
	f3dLine base_line;
public:
	CModRod();
	~CModRod();
	//
	CModModel* BelongModel(){return m_pBelongModel;}
	void SetBelongModel(CModModel* pModel){m_pBelongModel=pModel;}
	void SetKey(DWORD key){handle=key;}
	BOOL IsAngle(){return m_ciRodType==1;}
	BOOL IsLegRod(){return m_sLayer[0]=='L';}
	int GetLength(){return ftoi(DISTANCE(base_line.startPt,base_line.endPt));}
	UCS_STRU BuildUcs(BOOL bToLds=TRUE);
	BOOL Create3dSolidModel(CSolidBody *pSolidBody,BOOL bToLds=TRUE);
	f3dLine GetBaseLineToLdsModel();
	BYTE GetLegQuad();
};
class CModTowerInstance
{
	long m_id;
	RODSET RodSet;
	NODESET NodeSet;
	CModHeightGroup* m_pBelongHG;
public:
	GEPOINT m_xBaseLocation[4];
public:
	CModTowerInstance(){m_pBelongHG=NULL;m_id=0;}
	void SetKey(DWORD key){m_id=(long)key;}
	void SetBelongHuGao(CModHeightGroup* pHeightGroup){m_pBelongHG=pHeightGroup;}
	CModHeightGroup* BelongHuGao(){return m_pBelongHG;}
	void SetBaseLocation(int iLegQuad,GEPOINT pos){
		if(m_xBaseLocation[iLegQuad-1].z<pos.z)
			m_xBaseLocation[iLegQuad-1]=pos;
	}
	GEPOINT GetBaseLocation(int iLegQuad){return m_xBaseLocation[iLegQuad-1];}
	//�ڵ�
	void AppendNode(CModNode* pNode){NodeSet.append(pNode);}
	int GetModNodeNum(){return NodeSet.GetNodeNum();}
	CModNode* EnumModNodeFir(){return NodeSet.GetFirst();}
	CModNode* EnumModNodeNext(){return NodeSet.GetNext();}
	//�˼�
	void AppendRod(CModRod* pRod){RodSet.append(pRod);}
	int GetModRodNum(){return RodSet.GetNodeNum();}
	CModRod* EnumModRodFir(){return RodSet.GetFirst();}
	CModRod* EnumModRodNext(){return RodSet.GetNext();}
};
class CModHeightGroup
{
	CModModel* m_pModel;
public:
	int m_iNo;					//���ߺ�
	int m_iBody;				//�Ͻӱ���
	double m_fNamedHeight;		//���Ƹ߶�
	CXhChar50 m_sHeightName;	//��������
	CFGWORD m_dwLegCfgWord;		//������ĺ�
	int m_arrActiveQuadLegNo[4];
	CHashListEx<CModTowerInstance> hashTowerInstance;
	CHashStrList<int> hashSubLegSerial;
public:
	CModHeightGroup();
	void SetKey(DWORD key){m_iNo=key;}
	void SetBelongModel(CModModel* pModel){m_pModel=pModel;}
	BYTE GetLegBitSerialFromSerialId(int serial);
	CModTowerInstance* GetTowerInstance(int legSerialQuad1, int legSerialQuad2, int legSerialQuad3, int legSerialQuad4);
};

struct MOD_HANG_NODE
{
	char m_ciWireType;		//������:'C'����|'E'����|'J'����
	char m_ciHangingStyle;	//�Ҵ����ͣ�0.����|'S'˫��|'V'V��
	BYTE m_ciLoopSerial;	//��·���
	BYTE m_ciPhaseSerial;	//�����
	BYTE m_ciHangOrder;		//�����
	BYTE m_ciHangDirect;	//�ҵ㳯��:'Q'ǰ��|'H'���
	char m_sHangName[50];	//�ҵ�����
	GEPOINT m_xHangPos;		//λ��
	//
	MOD_HANG_NODE(){
		m_ciLoopSerial=0;
		m_ciPhaseSerial=0;
		m_ciHangOrder=0;
		m_ciHangDirect=0;
		m_ciWireType=0;
		m_ciHangingStyle=0;
		strcpy(m_sHangName,"");
	}
	void Clone(MOD_HANG_NODE* pSrcHangNode)
	{
		m_ciWireType=pSrcHangNode->m_ciWireType;
		m_ciHangingStyle=pSrcHangNode->m_ciHangingStyle;
		m_ciLoopSerial=pSrcHangNode->m_ciLoopSerial;
		m_ciPhaseSerial=pSrcHangNode->m_ciPhaseSerial;
		m_ciHangOrder=pSrcHangNode->m_ciHangOrder;
		m_ciHangDirect=pSrcHangNode->m_ciHangDirect;
		m_xHangPos=pSrcHangNode->m_xHangPos;
		strcpy(m_sHangName,pSrcHangNode->m_sHangName);
	}
};
struct SUB_LEG_INFO{
	double m_fLegH;		//���ȸ߶�
	NODESET legNodeSet;	//�Ȳ��ڵ㼯��
	RODSET legRodSet;
	//
	SUB_LEG_INFO(){m_fLegH=0;}
};
class CLegItem
{
public:
	long m_hTagNode;
	int m_iLegNo;		//
	double m_fSegmentH;	//���ò��ֶθ�
	double m_fMaxLegH;	//��ȸ�
	GEPOINT m_maxLegPt;	//�������
	NODESET segmentNodeSet;	//���зֶνڵ�
	RODSET segmentRodSet;	//
	ATOM_LIST<SUB_LEG_INFO> subLegInfoList;
public:
	CLegItem(){m_fSegmentH=0;m_fMaxLegH=0;};
	~CLegItem(){;}
};
class CBodyItem
{
public:
	long m_hTagNode;		//������ֹ�����ڵ�(�ڶ�����Zֵ���ڵ�)
	double m_fBodyH;		//����߶�
	int m_iLegS;			//�����¿�ʼ�������
	NODESET bodyNodeSet;	//
	RODSET bodyRodSet;
public:
	CBodyItem(){m_hTagNode=0;m_fBodyH=0;m_iLegS=0;}
	~CBodyItem(){;}
};

class CModModel
{
public:
	long m_iSerial;
	double m_fTowerHeight;
	ATOM_LIST<CLegItem> m_listLegItem;
	ATOM_LIST<CBodyItem> m_listBodyItem;
	ARRAY_LIST<MOD_HANG_NODE> m_listGuaNode;
private:
	CHashListEx<CModHeightGroup> ModHeightGroup;
	CHashListEx<CModRod> ModRods;
	CHashListEx<CModNode> ModNodes;
protected:
	void AmendModData();
public:
	CModModel(long serial=0);
	~CModModel();
	//
	static char QueryBriefMatMark(const char* sMatMark);
	static void QuerySteelMatMark(char cMat,char* sMatMark);
	static BOOL IsUTF8File(const char* mod_file);
	//
	void Empty();
	GECS BuildUcsByModCS();	//����LDSģ������ϵ����MODģ������ϵΪ���ײ��գ�
	long GetSerialId(){return m_iSerial;}
	void ReadModFile(FILE* fp,BOOL bUtf8=FALSE);
	void WriteModFileByUtf8(FILE* fp);
	void WriteModFileByAnsi(FILE* fp);
	//
	int GetHeightGroupNum(){return ModHeightGroup.GetNodeNum();}
	CModHeightGroup* AppendHeightGroup(DWORD key){return ModHeightGroup.Add(key);}
	CModHeightGroup* EnumFirstHGroup(){return ModHeightGroup.GetFirst();}
	CModHeightGroup* EnumNextHGroup(){return ModHeightGroup.GetNext();}
	CModHeightGroup* GetHeightGroup(int iNo);
	CModHeightGroup* GetHeightGroup(const char* sName);
	//
	CModNode* AppendNode(DWORD key){return ModNodes.Add(key);}
	CModNode* FindNode(DWORD key){return ModNodes.GetValue(key);}
	CModNode* EnumFirstNode(){return ModNodes.GetFirst();}
	CModNode* EnumNextNode(){return ModNodes.GetNext();}
	//
	CModRod* AppendRod(DWORD key){return ModRods.Add(key);}
	CModRod* FindRod(DWORD key){return ModRods.GetValue(key);}
	CModRod* EnumFirstRod(){return ModRods.GetFirst();}
	CModRod* EnumNextRod(){return ModRods.GetNext();}
};

class CModModelFactory{
public:
	static CModModel* CreateModModel();
	static CModModel* ModModelFromSerial(long serial);
	static bool Destroy(long serial);
};