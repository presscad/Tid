// TIDCore.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "TidCplus.h"
#include "TIDModel.h"
#include "f_ent.h"

/*#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif*/

//////////////////////////////////////////////////////////////////////////
// CTidModelFactory
static CHashPtrList<CTidModel>localHashTidModels;
class CTidModelsLife{
public:
	~CTidModelsLife(){localHashTidModels.Empty();}
};
CTidModelsLife modelsLife;

ITidModel* CTidModelFactory::CreateTidModel()
{
	int iNo=1;
	do{
		if(localHashTidModels.GetValue(iNo)!=NULL)
			iNo++;
		else	//�ҵ�һ���պ�
			break;
	}while(true);
	CTidModel* pModel = localHashTidModels.Add(iNo);
	return pModel;
};
ITidModel* CTidModelFactory::TidModelFromSerial(long serial)
{
	return localHashTidModels.GetValue(serial);
}
bool CTidModelFactory::Destroy(long serial)
{
	for(CTidModel *pTidModel=localHashTidModels.GetFirst();pTidModel;pTidModel=localHashTidModels.GetNext())
	{
		if(pTidModel->GetSerialId()==serial)
			return localHashTidModels.DeleteCursor(TRUE)==TRUE;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// TidArcline
bool TID_COORD3D::IsEqual(double ex,double ey,double ez,double epsilon/*=eps*/) const
{
	if(fabs(x-ex)>epsilon)
		return false;
	else if(fabs(y-ey)>epsilon)
		return false;
	else if(fabs(z-ez)>epsilon)
		return false;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////
// TidArcline
TidArcline::TidArcline()
{
	sector_angle=0;
	work_norm.Set(0,0,1);
	column_norm.Set(0,0,1);
	posStart.Set(1,0,0);
	posEnd.Set(-1,0,0);
	radius = 1;
}

TID_COORD3D TidArcline::StartPosition() const{return posStart;}
TID_COORD3D TidArcline::EndPosition() const{return posEnd;}
TID_COORD3D TidArcline::ColumnNorm() const{return column_norm;}
TID_COORD3D TidArcline::WorkNorm() const{return work_norm;}
TID_COORD3D TidArcline::Center() const{return center;}
double TidArcline::Radius() const{return radius;}
double TidArcline::SectorAngle() const{return sector_angle;}//�����Ƶ�λ
int TidArcline::ToByteArr(char* buf)	//ֱ��48Bytes,Բ��112Bytes,��Բ��136Bytes;ע��ֻ���������Ϣ����
{
	memcpy(buf,(double*)posStart,24);
	memcpy(buf+24,(double*)posEnd,24);
	if(sector_angle==0)
		return 48;	//ֱ��
	else			//Բ����
	{
		memcpy(buf+48,&sector_angle,8);	//�����Ƶ�λ
		memcpy(buf+56,&radius,8);
		memcpy(buf+64,(double*)center,24);
		memcpy(buf+88,(double*)work_norm,24);
		if(!column_norm.IsZero()&&!column_norm.IsEqual(work_norm.x,work_norm.y,work_norm.z))	//��Բ��
		{
			memcpy(buf+112,(double*)column_norm,24);
			return 136;
		}
		else
			return 112;
	}
}
void TidArcline::FromByteArr(char* buf,DWORD buf_size)//�ӻ����л�ԭ����ֱ��
{
	memcpy((double*)posStart,buf,24);
	memcpy((double*)posEnd,buf+24,24);
	if(buf_size>=112)
	{	//Բ����
		memcpy(&sector_angle,buf+48,8);	//�����Ƶ�λ
		memcpy(&radius,buf+56,8);
		memcpy((double*)center,buf+64,24);
		memcpy((double*)work_norm,buf+88,24);
		if(buf_size>=136)
			memcpy((double*)column_norm,buf+112,24);
		else
			column_norm.Set(0,0,0);
	}
	else
		sector_angle=0;
}
double TidArcline::Length()//Բ������
{
	f3dArcLine arcline;
	char pool[200]={0};
	DWORD uPoolSize=ToByteArr(pool);
	arcline.FromByteArr(pool,uPoolSize);
	return arcline.Length();
}
TID_COORD3D TidArcline::PositionInAngle(double posAngle)	//�����Ƶ�λ
{
	f3dArcLine arcline;
	char pool[200]={0};
	DWORD uPoolSize=ToByteArr(pool);
	arcline.FromByteArr(pool,uPoolSize);
	GEPOINT pos=arcline.PositionInAngle(posAngle);
	return TID_COORD3D(pos);
}
TID_COORD3D TidArcline::TangentVecInAngle(double posAngle)	//��ʱ����תΪ��������,�����Ƶ�λ
{
	f3dArcLine arcline;
	char pool[200]={0};
	DWORD uPoolSize=ToByteArr(pool);
	arcline.FromByteArr(pool,uPoolSize);
	GEPOINT vec=arcline.TangentVecInAngle(posAngle);
	return TID_COORD3D(vec);
};
