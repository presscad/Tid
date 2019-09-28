// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TIDCORE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TIDCORE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TIDCORE_EXPORTS
#define TIDCORE_API __declspec(dllexport)
#else
#define TIDCORE_API __declspec(dllimport)
#endif
#pragma once

//----���ʿ�
//<class ISteelMaterialLib begin>
UINT TIDCORE_API SteelMaterialLib_GetCount(WPARAM hISteelMaterialLib);
void TIDCORE_API SteelMaterialLib_GetSteelMatAt(WPARAM hISteelMaterialLib,UINT i,char* tid_steelmat);// TID_STEELMAT=9�ֽ�
char TIDCORE_API SteelMaterialLib_QuerySteelBriefSymbol(WPARAM hISteelMaterialLib,const char*steelmark);
//TODO:nameCode��Ҫ����
bool TIDCORE_API SteelMaterialLib_QuerySteelNameCode(WPARAM hISteelMaterialLib,char cBriefSymbol,char* nameCode);
//</class ISteelMaterialLib end>
//ʵ��
/* ����Ϊ���ߺ������ԣã����ţ�������Ҫ������Ա�����Լ�д�ã��汾�Ĵ��� wjh-2016.1.23
//<class TidArcline begin>
int TIDCORE_API TidArcline_ToByteArr(WPARAM hTidArcline,char* buf);
void TIDCORE_API TidArcline_FromByteArr(WPARAM hTidArcline,char* buf,DWORD buf_size);
void TIDCORE_API TidArcline_StartPosition(WPARAM hTidArcline,double* tid_cord3d); //TID_COORD3D==24�ֽ�
void TIDCORE_API  TidArcline_EndPosition(WPARAM hTidArcline,double* tid_cord3d);//TID_COORD3D==24�ֽ�
void TIDCORE_API TidArcline_ColumnNorm(WPARAM hTidArcline,double* tid_cord3d);//TID_COORD3D==24�ֽ�
void TIDCORE_API TidArcline_WorkNorm(WPARAM hTidArcline,double* tid_cord3d);//TID_COORD3D==24�ֽ�
void TIDCORE_API TidArcline_Center(WPARAM hTidArcline,double* tid_cord3d);//TID_COORD3D==24�ֽ�
double TIDCORE_API TidArcline_Radius(WPARAM hTidArcline);
double TIDCORE_API TidArcline_SectorAngle(WPARAM hTidArcline);//�����Ƶ�λ
double TIDCORE_API TidArcline_Length(WPARAM hTidArcline);//Բ������
void  TIDCORE_API TidArcline_PositionInAngle(WPARAM hTidArcline,double posAngle,double* tid_cord3d);//�����Ƶ�λ TID_COORD3D==24�ֽ�
void TIDCORE_API TidArcline_TangentVecInAngle(WPARAM hTidArcline,double posAngle,double* tid_cord3d);	//��ʱ����תΪ��������,�����Ƶ�λ TID_COORD3D==24�ֽ�
//<class TidArcline end>
*/
//<class TidRawSolidEdge begin>
BYTE TIDCORE_API TidRawSolidEdge_EdgeType(WPARAM hTidRawSolidEdge);
BYTE TIDCORE_API TidRawSolidEdge_SolidDrawWidth(WPARAM hTidRawSolidEdge);
DWORD TIDCORE_API TidRawSolidEdge_LineStartId(WPARAM hTidRawSolidEdge);
DWORD TIDCORE_API TidRawSolidEdge_LineEndId(WPARAM hTidRawSolidEdge);
void TIDCORE_API TidRawSolidEdge_Center(WPARAM hTidRawSolidEdge,double* tid_cord3d);//TID_COORD3D==24�ֽ�
void TIDCORE_API TidRawSolidEdge_WorkNorm(WPARAM hTidRawSolidEdge,double* tid_cord3d);//TID_COORD3D==24�ֽ�
void TIDCORE_API TidRawSolidEdge_ColumnNorm(WPARAM hTidRawSolidEdge,double* tid_cord3d);//TID_COORD3D==24�ֽ�
//<class TidRawSolidEdge end>
//--------------------------------------------
//<class IFaceLoop begin>
WORD TIDCORE_API FaceLoop_EdgeLineNum(WPARAM hIFaceLoop);
bool TIDCORE_API FaceLoop_EdgeLineDataAt(WPARAM hIFaceLoop,int index,double* pArcline);//pArcline ����Ϊ(TidArcline*) 
WPARAM TIDCORE_API FaceLoop_EdgeLineAt(WPARAM hIFaceLoop,int index);// return  ITidRawSolidEdge*
//<class IFaceLoop end>

//<class IRawSolidFace begin>
COLORREF TIDCORE_API RawSolidFace_MatColor(WPARAM hIRawSolidFace);	//TODO	// �����ڼ�¼�����������Ϣ(����ʵ�) 
DWORD TIDCORE_API RawSolidFace_FaceId(WPARAM hIRawSolidFace);
WORD TIDCORE_API RawSolidFace_InnerLoopNum(WPARAM hIRawSolidFace);
void TIDCORE_API RawSolidFace_WorkNorm(WPARAM hIRawSolidFace,double* tid_cord3d);// TID_COORD3D = 24�ֽ�
WPARAM TIDCORE_API RawSolidFace_InnerLoopAt(WPARAM hIRawSolidFace,int i);// return IFaceLoop*
WPARAM TIDCORE_API RawSolidFace_OutterLoop(WPARAM hIRawSolidFace);// reurn IFaceLoop* 
//<class IRawSolidFace end>

//<class IFacetCluster begin>
BYTE TIDCORE_API FacetCluster_Mode(WPARAM hIFacetCluster);//������������glBegin()����Ҫ�Ļ���ģʽ
void  TIDCORE_API FacetCluster_Normal(WPARAM hIFacetCluster,double* tid_cord3d);//TID_COORD3D=24�ֽ�
WORD TIDCORE_API FacetCluster_FacetNumber(WPARAM hIFacetCluster);
WORD TIDCORE_API FacetCluster_VertexNumber(WPARAM hIFacetCluster);
void TIDCORE_API FacetCluster_VertexAt(WPARAM hIFacetCluster,int index,double* tid_cord3d);  //TODO TID_COORD3D = 24�ֽ�
//<class IFacetCluster end>

//<class ITidBasicFace begin>
COLORREF TIDCORE_API TidBasicFace_Color(WPARAM hITidBasicFace);
WORD  TIDCORE_API TidBasicFace_FacetClusterNumber(WPARAM hITidBasicFace);
WPARAM TIDCORE_API TidBasicFace_FacetClusterAt(WPARAM hITidBasicFace,int index);
//<class ITidBasicFace end>

//<class ITidSolidBody begin>
int TIDCORE_API ITidSolidBody_KeyPointNum(WPARAM hITidSolidBody);
//TODO:��ʱ�����Ŵ˺���
//char* TIDCORE_API ITidSolidBody_SolidBufferPtr(WPARAM hITidSolidBody);
DWORD TIDCORE_API ITidSolidBody_SolidBufferLength(WPARAM hITidSolidBody);
void TIDCORE_API ITidSolidBody_ReleaseTemporaryBuffer(WPARAM hITidSolidBody);
void TIDCORE_API ITidSolidBody_GetKeyPointAt(WPARAM hITidSolidBody,int i,double* tid_cord3d); //TODO TID_COORD3D = 24�ֽ�
int TIDCORE_API ITidSolidBody_KeyEdgeLineNum(WPARAM hITidSolidBody);
/* TidArcline ռ�ÿռ�17*double
struct TidArcline{
protected:
	TID_COORD3D posStart,posEnd;
	TID_COORD3D center;
	TID_COORD3D column_norm;
	TID_COORD3D work_norm;
	double radius;
	double sector_angle;//�����Ƶ�λ
}
*/
bool TIDCORE_API ITidSolidBody_GetKeyEdgeLineDataAt(WPARAM hITidSolidBody,int i,double* line_data);//TidArcline& line);
WPARAM TIDCORE_API ITidSolidBody_GetKeyEdgeLineAt(WPARAM hITidSolidBody,int i); //return ITidRawSolidEdge*
int TIDCORE_API ITidSolidBody_PolyFaceNum(WPARAM hITidSolidBody);
WPARAM TIDCORE_API ITidSolidBody_GetPolyFaceAt(WPARAM hITidSolidBody,int i);//return IRawSolidFace* 
int TIDCORE_API ITidSolidBody_BasicFaceNum(WPARAM hITidSolidBody);
WPARAM TIDCORE_API ITidSolidBody_GetBasicFaceAt(WPARAM hITidSolidBody,int i);//return ITidBasicFace*
bool TIDCORE_API ITidSolidBody_SplitToBasicFacets(WPARAM hITidSolidBody);
//��ʵ���װ������ϵfromACS��λ��װ������ϵtoACS
void  TIDCORE_API ITidSolidBody_TransACS(WPARAM hITidSolidBody,const double* fromACS,const double* toACS); // TODO
void  TIDCORE_API ITidSolidBody_TransFromACS(WPARAM hITidSolidBody,const double* fromACS); // TODO
void  TIDCORE_API ITidSolidBody_TransToACS(WPARAM hITidSolidBody,const double* toACS); // TODO
//<class ITidSolidBody end>


//<class ITidBoltNut begin>
short  TIDCORE_API TidBoltNut_GetDiameter(WPARAM hITidBoltNut); 
WPARAM TIDCORE_API TidBoltNut_GetSolidBody(WPARAM hITidBoltNut);//return ITidSolidBody*
//<class ITidBoltNut end>

//<class IBoltSizeSpec begin>
UINT  TIDCORE_API BoltSizeSpec_GetSeriesId(WPARAM hIBoltSizeSpec);
short  TIDCORE_API BoltSizeSpec_GetDiameter(WPARAM hIBoltSizeSpec);
short  TIDCORE_API BoltSizeSpec_GetLenValid(WPARAM hIBoltSizeSpec);
short  TIDCORE_API BoltSizeSpec_GetLenNoneThread(WPARAM hIBoltSizeSpec);
double  TIDCORE_API BoltSizeSpec_GetTheoryWeight(WPARAM hIBoltSizeSpec);
short  TIDCORE_API BoltSizeSpec_GetSpec(WPARAM hIBoltSizeSpec,char* spec);
WPARAM  TIDCORE_API BoltSizeSpec_GetBoltSolid(WPARAM hIBoltSizeSpec);// retturn ITidSolidBody*
WPARAM  TIDCORE_API BoltSizeSpec_GetNutSolid(WPARAM hIBoltSizeSpec);// retturn ITidSolidBody*
//<class IBoltSizeSpec end>

//<class IBoltSeries begin>
UINT TIDCORE_API BoltSeries_GetSeriesId(WPARAM hIBoltSeries);
short TIDCORE_API BoltSeries_GetName(WPARAM hIBoltSeries,char* name);
int TIDCORE_API BoltSeries_GetCount(WPARAM hIBoltSeries );
short TIDCORE_API BoltSeries_GetBoltNutCount(WPARAM hIBoltSeries );
short TIDCORE_API BoltSeries_GetWasherCount(WPARAM hIBoltSeries );
//bool TIDCORE_API BoltSeries_IsFootNail(WPARAM hIBoltSeries);
//bool TIDCORE_API BoltSeries_IsBurglarproof(WPARAM hIBoltSeries);
WPARAM TIDCORE_API BoltSeries_EnumBoltFirst(WPARAM hIBoltSeries);//IBoltSizeSpec*
WPARAM TIDCORE_API BoltSeries_EnumBoltNext(WPARAM hIBoltSeries);//IBoltSizeSpec*
WPARAM TIDCORE_API BoltSeries_GetBoltSizeSpecById(WPARAM hIBoltSeries,int id);//IBoltSizeSpec*
//<class IBoltSeries end>

//<class IBoltSeriesLib begin>
int  TIDCORE_API BoltSeriesLib_GetCount(WPARAM hIBoltSeriesLib);
WPARAM  TIDCORE_API BoltSeriesLib_GetBoltSeriesAt(WPARAM hIBoltSeriesLib,int i);// return IBoltSeries*
WPARAM TIDCORE_API BoltSeriesLib_GetBoltSizeSpec(WPARAM hIBoltSeriesLib,int seriesId,int sizeSpecId);// return IBoltSizeSpec*
//<class IBoltSeriesLib end>

//<class ITidPart begin>
int  TIDCORE_API ITidPart_GetPartType(WPARAM hITidPart);
UINT TIDCORE_API ITidPart_GetSerialId(WPARAM hITidPart);
char  TIDCORE_API ITidPart_GetBriefMark(WPARAM hITidPart);
WORD  TIDCORE_API ITidPart_GetLength(WPARAM hITidPart);
double TIDCORE_API ITidPart_GetWidth(WPARAM hITidPart);
double TIDCORE_API ITidPart_GetThick(WPARAM hITidPart);
double TIDCORE_API ITidPart_GetHeight(WPARAM hITidPart);
double TIDCORE_API ITidPart_GetWeight(WPARAM hITidPart);
WORD TIDCORE_API ITidPart_GetStateFlag(WPARAM hITidPart);
short TIDCORE_API ITidPart_GetSegStr(WPARAM hITidPart,char* segstr);
short TIDCORE_API ITidPart_GetSpec(WPARAM hITidPart,char* sizeSpec);
short TIDCORE_API ITidPart_GetLabel(WPARAM hITidPart,char*label);
short TIDCORE_API ITidPart_GetFuncType(WPARAM hITidPart);
WPARAM TIDCORE_API ITidPart_GetSolidPart(WPARAM hITidPart);	//ITidSolidBody*
UINT TIDCORE_API ITidPart_GetProcessBuffBytes(WPARAM hITidPart,char* processbytes,UINT maxBufLength=0);
//<class ITidPart end>

//<class ITidPartsLib begin>
int  TIDCORE_API TidPartsLib_GetCount(WPARAM hITidPartsLib);
WPARAM TIDCORE_API TidPartsLib_GetTidPartBySerialId(WPARAM hITidPartsLib,int i);// return ITidPart*
//<class IBoltSeriesLib end>

//<class ITidAssemblePart begin>
WPARAM TIDCORE_API TidAssemblePart_GetPart(WPARAM hITidAssemblePart); //return ITidPart *
bool TIDCORE_API TidAssemblePart_IsHasBriefRodLine(WPARAM hITidAssemblePart);
void TIDCORE_API TidAssemblePart_BriefLineStart(WPARAM hITidAssemblePart, double* tid_cord3d); // TID_COORD3D = 24�ֽ�
void TIDCORE_API TidAssemblePart_BriefLineEnd(WPARAM hITidAssemblePart, double* tid_cord3d); // TID_COORD3D = 24�ֽ�
int  TIDCORE_API TidAssemblePart_GetStartNodeId(WPARAM hITidAssemblePart);
int  TIDCORE_API TidAssemblePart_GetEndNodeId(WPARAM hITidAssemblePart);
void TIDCORE_API TidAssemblePart_GetAcs(WPARAM hITidAssemblePart, double* tid_cs); // TID_CS = 24*4�ֽ� 
WPARAM TIDCORE_API TidAssemblePart_GetSolidPart(WPARAM hITidAssemblePart);  //return ITidSolidBody*
//<class ITidAssemblePart end>

//<class ITidAssembleBolt begin>
WPARAM TIDCORE_API TidAssembleBolt_GetTidBolt(WPARAM hITidAssembleBolt); //return IBoltSizeSpec*
void  TIDCORE_API TidAssembleBolt_GetAcs(WPARAM hITidAssembleBolt,double* tid_cs); // TID_CS=24*4�ֽ�
WPARAM TIDCORE_API TidAssembleBolt_GetBoltSolid(WPARAM hITidAssembleBolt);//return ITidSolidBody*
WPARAM TIDCORE_API TidAssembleBolt_GetNutSolid(WPARAM hITidAssembleBolt);//return ITidSolidBody*
//<class ITidAssembleBolt end>

//<class ITidHeightGroup begin>
int TIDCORE_API TidHeightGroup_GetSerialId(WPARAM hITidHeightGroup);
int TIDCORE_API TidHeightGroup_GetName(WPARAM hITidHeightGroup,char *name,UINT maxBufLength=0);
int TIDCORE_API TidHeightGroup_GetLegSerialArr(WPARAM hITidHeightGroup,int* legSerialArr);
int TIDCORE_API TidHeightGroup_GetLegSerial(WPARAM hITidHeightGroup,double heightDifference);
double TIDCORE_API TidHeightGroup_GetLegHeightDifference(WPARAM hITidHeightGroup,int legSerial);
WPARAM TIDCORE_API TidHeightGroup_GetTowerInstance(WPARAM hITidHeightGroup,int legSerialQuad1, int legSerialQuad2, 
	                                           int legSerialQuad3, int legSerialQuad4); // return   ITidTowerInstance*  
//<class ITidHeightGroup end>


//<class ITidTowerInstance begin>
short TIDCORE_API TidTowerInstance_GetLegSerialIdByQuad(WPARAM hTidTowerInstance,short siQuad);
WPARAM TIDCORE_API TidTowerInstance_BelongHeightGroup(WPARAM hTidTowerInstance); //return ITidHeightGroup*
WPARAM TIDCORE_API TidTowerInstance_EnumAssembleBoltFirst(WPARAM hTidTowerInstance);//return ITidAssembleBolt*
WPARAM TIDCORE_API TidTowerInstance_EnumAssembleBoltNext(WPARAM hTidTowerInstance); //return ITidAssembleBolt*
WPARAM TIDCORE_API TidTowerInstance_EnumAssemblePartFirst(WPARAM hTidTowerInstance); //return ITidAssemblePart*
WPARAM TIDCORE_API TidTowerInstance_EnumAssemblePartNext(WPARAM hTidTowerInstance); //return ITidAssemblePart*
//<class ITidTowerInstance end>

//��ģ��
UINT TIDCORE_API TidModel_GetSerialId(WPARAM hITidModel);
int  TIDCORE_API TidModel_GetTowerTypeName(WPARAM hITidModel,char* towerTypeName,UINT maxBufLength=0);
void TIDCORE_API TidModel_ModelCoordSystem(WPARAM hITidModel,double* tid_cs);	//TID_CS=24*4�ֽ�
WPARAM TIDCORE_API TidModel_GetSteelMatLibrary(WPARAM hITidModel);			//return ISteelMaterialLib*
WPARAM TIDCORE_API TidModel_GetBoltLibrary(WPARAM hITidModel);				//return IBoltSeriesLib*
WPARAM TIDCORE_API TidModel_GetTidPartsLib(WPARAM hITidModel);				//return ITidPartsLib*
short TIDCORE_API TidModel_HeightGroupCount(WPARAM hITidModel);
WPARAM TIDCORE_API TidModel_GetHeightGroupAt(WPARAM hITidModel,short i);	//return ITidHeightGroup*
bool TIDCORE_API TidModel_InitTidBuffer(WPARAM hITidModel,const char* src_buf,UINT buf_len);
bool TIDCORE_API TidModel_ReadTidFile(WPARAM hITidModel,const char* file_path);

WPARAM TIDCORE_API Factory_CreateTidModel();  
//WPARAM TIDCORE_API Factory_TidModelFromSerial();
bool TIDCORE_API Factory_DestroyTidModel(WPARAM hITidModel);
