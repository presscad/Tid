#include "StdAfx.h"
#include ".\solidtowermodel.h"

static DWORD CFG_NO[32]={ 0X00000001,0X00000002,0X00000004,0X00000008,0X00000010,0X00000020,0X00000040,0X00000080,
						  0X00000100,0X00000200,0X00000400,0X00000800,0X00001000,0X00002000,0X00004000,0X00008000,
						  0X00010000,0X00020000,0X00040000,0X00080000,0X00100000,0X00200000,0X00400000,0X00800000,
						  0X01000000,0X02000000,0X04000000,0X08000000,0X10000000,0X20000000,0X40000000,0X80000000};

CFGWORD GetCfgWord(long iNo)	//��1��ʼ����
{
	CFGWORD cfgword(iNo);
	return cfgword;
}
CFGWORD CFGWORD::SetWordByNo(int iNo)
{
	iNo--;
	Clear();
	if(iNo>=0&&iNo<192)
	{
		int iWord=iNo/32;
		int iBit=iNo%32;
		word[iWord]=CFG_NO[iBit];
	}
	return *this;
}
BOOL CFGWORD::And(CFGWORD wcfg) const
{
	return (word[0]&wcfg.word[0])||(word[1]&wcfg.word[1])||(word[2]&wcfg.word[2])||(word[3]&wcfg.word[3])||(word[4]&wcfg.word[4])||(word[4]&wcfg.word[5]);
}
BOOL CFGWORD::IsEqual(CFGWORD cfgword)
{
	return word[0]==cfgword.word[0]&&word[1]==cfgword.word[1] && 
		word[2]==cfgword.word[2]&&word[3]==cfgword.word[3]&&word[4]==cfgword.word[4]&&word[5]==cfgword.word[5];
}
BOOL CFGWORD::IsHasNo(int iNo)
{
	return And(GetCfgWord(iNo));
}
///////////////////////////////////////////////////////////////////////////////////////////////
//���ַ����͵İ汾��ת��Ϊһ������������"1.01.3.21"-->1 01 03 21
long FromStringVersion(const char* version)
{
	char local_version[20]="";
	strncpy(local_version,version,20);
	char *key=strtok(local_version," .,-");
	UINT version_item[4]={0};
	int n,i=0;
	while(key!=NULL&&i<4)
	{
		n=(int)strlen(key);
		if(n==1)
			version_item[i]=key[0]-'0';
		else if(n>1)
			version_item[i]=(key[0]-'0')*10+key[1]-'0';
		key=strtok(NULL,".,-");
		i++;
	}
	long nVersion=version_item[0]*1000000+version_item[1]*10000+version_item[2]*100+version_item[3];
	//long nVersion=version_item[0]*lic.ConstE6()+version_item[1]*lic.ConstE4()+version_item[2]*lic.ConstE2()+version_item[3];
	return nVersion;
}
//�������ʾ�汾��1��,�������ʾͬ�汾�������ʾ�汾��1��
int CompareVersion(const char* version1,const char* version2)
{
	if(version1==NULL)
		return 1;
	else if(version2==NULL)
		return -1;
	long nVersion1=FromStringVersion(version1);
	long nVersion2=FromStringVersion(version2);
	if(nVersion1>nVersion2)
		return 1;
	else if(nVersion1<nVersion2)
		return -1;
	else
		return 0;
}
CSolidPartModel::CSolidPartModel()
{
	cLegQuad=0;
}
CSolidPartModel::~CSolidPartModel()
{
	;
}
///////////////////////////////////////////////////////////////////////////////////////////////
TOWER_MODULE CModuleSection::GetModuleAt(int i)
{
	TOWER_MODULE module;
	BYTE* pBodyNo=(BYTE*)BufferPtr()+1+21*i;
	module.m_cBodyNo=*pBodyNo;
	int record_n=25;
	if(CompareVersion(m_sVersion,"1.1")>=0)
	{
		BYTE* pcbLegInfo=pBodyNo+1;
		module.m_cbLegInfo=*pcbLegInfo;
		memcpy(&module.m_dwLegCfgWord,pBodyNo+2,24);
		record_n=26;	//V1.1�����˼�����Ϣ����
	}
	else
		memcpy(&module.m_dwLegCfgWord,pBodyNo+1,24);
	for(BYTE j=1;j<=192;j++)
	{
		if(module.m_dwLegCfgWord.IsHasNo(j))
		{
			module.m_arrActiveQuadLegNo[0]=module.m_arrActiveQuadLegNo[1]=
			module.m_arrActiveQuadLegNo[2]=module.m_arrActiveQuadLegNo[3]=j;
			break;
		}
	}
	//��ȡ���߷��������
	char* pNameSection=BufferPtr()+1+record_n*GetModuleCount();
	CBuffer pool(pNameSection,GetModuleCount()*100);	//��֪�����������峤�ȣ�ֻ�ܸ���һ���϶��Ƚϴ�Ļ���ռ�
	for(int j=0;j<i;j++)
	{
		UINT uLen=pool.ReadStringLength();
		pool.Offset(uLen);
	}
	pool.ReadString(module.name,51);
	return module;
}
CBlockSection::CBlockSection(DWORD zeroAddrOffset,char* buf/*=NULL*/,DWORD size/*=0*/){
	m_dwZeroAddrOffset=zeroAddrOffset;
	m_data=buf;
	m_dwBufSize=size;
}
TOWER_BLOCK CBlockSection::GetBlockAt(int i)
{
	TOWER_BLOCK block;
	CBuffer buf(BufferPtr(),BufferLength());
	buf.SeekPosition(2+100*i);
	buf.ReadPoint(block.lcs.origin);
	buf.ReadPoint(block.lcs.axis_x);
	buf.ReadPoint(block.lcs.axis_y);
	buf.ReadPoint(block.lcs.axis_z);
	DWORD name_addr;
	buf.ReadDword(&name_addr);
	buf.SeekPosition(AddrGtoL(name_addr));
	buf.ReadString(block.name,50);
	return block;
}
BOLT_INFO CBoltSeries::GetBoltSizeAt(int i)
{
	CBuffer buf(BufferPtr(),BufferLength());
	BYTE d_count;
	WORD size_count;
	buf.ReadByte(&d_count);
	buf.Offset(2);	//ƫ��1B��Ȧ������1B��ñ����
	buf.ReadWord(&size_count);
	if(CompareVersion(m_sVersion,"1.1")>=0)
	{	//����ͨ������2B������2B
		buf.Offset(23);	//ƫ��23B��˨������
		buf.Offset(i*36);
	}
	else
		buf.Offset(i*32);
	BOLT_INFO bolt;
	buf.ReadWord(&bolt.d);			//��˨ֱ��
	buf.ReadWord(&bolt.L);			//��Ч��(mm)
	buf.ReadWord(&bolt.Lnt);		//�޿۳�
	buf.ReadDouble(&bolt.weight);	//kg
	buf.Read(bolt.spec,18);	//�̶����ȵ���˨��������ַ�����ĩβ0��ֹ�ַ���
	//������˨��ʵ�������ڴ�
	DWORD offset,len;
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.SeekPosition(5+23+size_count*36+d_count*6+4*i);
	else
		buf.SeekPosition(5+size_count*32+d_count*6+4*i);
	buf.ReadDword(&offset);
	buf.SeekPosition(AddrGtoL(offset));
	buf.ReadDword(&len);
	bolt.solidOfBolt.AttachBuffer(buf.GetCursorBuffer(),len);
	//������ñʵ�������ڴ�
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.SeekPosition(5+23+size_count*32);
	else
		buf.SeekPosition(5+size_count*32);
	BYTE di;
	for(di=0;di<d_count;di++)
	{
		WORD rd;
		buf.ReadWord(&rd);
		if(rd==bolt.d)
		{
			buf.ReadDword(&offset);	//��˨ñʵ�����ݴ洢��ַ
			buf.SeekPosition(AddrGtoL(offset));
			buf.ReadDword(&len);
			bolt.solidOfCap.AttachBuffer(buf.GetCursorBuffer(),len);
			break;
		}
		else
			buf.Offset(4);
	}
	if(di==d_count)
		int b=3;//TODO: ����δ����
	return bolt;
}
bool CBoltSeries::GetBoltCapSolidBody(int indexId, CSolidBody& body)
{
	CBuffer buf(BufferPtr(),BufferLength());
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.SeekPosition(5+23+BoltSizeCount()*36+indexId*6-4);
	else
		buf.SeekPosition(5+BoltSizeCount()*32+indexId*6-4);
	DWORD offset,len;
	buf.Offset(2);	//��˨ֱ��
	buf.ReadDword(&offset);
	buf.SeekPosition(AddrGtoL(offset));
	buf.ReadDword(&len);
	body.ReadFrom(&buf,len);
	return true;
}
bool CBoltSeries::GetBoltSolidBody(int indexId, CSolidBody& body)
{
	CBuffer buf(BufferPtr(),BufferLength());
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.SeekPosition(5+23+BoltSizeCount()*36+BoltDCount()*6+indexId*4-4);
	else
		buf.SeekPosition(5+BoltSizeCount()*32+BoltDCount()*6+indexId*4-4);
	DWORD offset,len;
	buf.ReadDword(&offset);
	buf.SeekPosition(AddrGtoL(offset));
	buf.ReadDword(&len);
	body.ReadFrom(&buf,len);
	return true;
}

CBoltSeries CBoltSection::GetBoltSeriesAt(int i)
{
	CBuffer buf(BufferPtr(),BufferLength());
	buf.SeekPosition(1+i*4);
	DWORD offset,len;
	buf.ReadDword(&offset);
	buf.SeekPosition(AddrGtoL(offset));
	buf.ReadDword(&len);
	return CBoltSeries(ZeroAddrOffset()+buf.GetCursorPosition(),buf.GetCursorBuffer(),len);
}

CMaterialLibrary CPartSection::GetMatLibrary()
{
	CBuffer buf(BufferPtr(),BufferLength());
	BYTE mat_n;
	buf.ReadByte(&mat_n);
	DWORD part_n;
	buf.ReadDword(&part_n);
	return CMaterialLibrary(mat_n,buf.GetCursorBuffer(),mat_n*8);
}
PART_INFO CPartSection::GetPartInfoAt(int indexId)
{
	BYTE mat_n;
	DWORD part_n;
	CBuffer buf(BufferPtr(),BufferLength());
	buf.ReadByte(&mat_n);
	buf.ReadDword(&part_n);
	buf.Offset(mat_n*8);
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.Offset((indexId-1)*33);
	else
		buf.Offset((indexId-1)*32);
	PART_INFO part;
	buf.ReadWord(&part.wModelSpace);
	buf.ReadByte(&part.cPartType);
	buf.ReadWord(&part.wStateFlag);
	buf.ReadByte(&part.cMaterial);
	buf.ReadDword(&part.dwSeg);
	buf.ReadFloat(&part.fWidth);
	buf.ReadFloat(&part.fThick);
	buf.ReadFloat(&part.fHeight);
	buf.ReadWord(&part.wLength);
	buf.ReadFloat(&part.fWeight);
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.ReadByte(&part.cFuncType);
	buf.ReadDword(&part.addrAttachInfo);
	//��ȡ������Ϣ
	buf.SeekPosition(AddrGtoL(part.addrAttachInfo));
	DWORD size;
	buf.ReadDword(&size);
	part.solid.AttachBuffer(buf.GetCursorBuffer(),size);
	buf.Offset(size);
	buf.ReadString(part.sPartNo,16);
	buf.ReadString(part.spec,16);
	buf.ReadString(part.sNotes,50);
	buf.ReadDword(&size);	//��������������Ϣ�洢����
	buf.Offset(size);		//����Ҫ���������Ϣ�������Ե��˲�����Ϣ
	return part;
}
DWORD CAssembleSection::BlockAssemblyCount()
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD block_count;
	buf.ReadDword(&block_count);
	return block_count;
}
BLOCK_ASSEMBLY CAssembleSection::GetAssemblyAt(int indexId)
{
	CBuffer buf(BufferPtr(),BufferLength());
	buf.Offset(4+(indexId-1)*128);
	BLOCK_ASSEMBLY assembly;
	buf.ReadWord(&assembly.wIndexId);
	buf.ReadPoint(assembly.acs.origin);
	buf.ReadPoint(assembly.acs.axis_x);
	buf.ReadPoint(assembly.acs.axis_y);
	buf.ReadPoint(assembly.acs.axis_z);
	buf.ReadDword(&assembly.dwSeg);
	buf.ReadByte(&assembly.cLegQuad);
	buf.Read(&assembly.cfgword,24);
	buf.ReadByte(&assembly.reserved);
	return assembly;
}
CBoltAssemblySection CAssembleSection::BoltSection()
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD block_assembly_n,size;
	buf.ReadDword(&block_assembly_n);
	buf.Offset(block_assembly_n*128);
	buf.ReadDword(&size);
	return CBoltAssemblySection(buf.GetCursorBuffer(),size);
}
DWORD CBoltAssemblySection::AssemblyCount(bool bTowerSpace/*=true*/)
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD assemble_n;
	if(bTowerSpace)
		buf.Offset(4);
	buf.ReadDword(&assemble_n);
	return assemble_n;
}
BOLT_ASSEMBLY CBoltAssemblySection::GetAssemblyAt(int indexId,bool bTowerSpace/*=true*/)
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD block_bolt_n,tower_bolt_n;
	buf.ReadDword(&block_bolt_n);
	buf.ReadDword(&tower_bolt_n);

	BOLT_ASSEMBLY assembly;
	if(bTowerSpace)
	{
		buf.Offset(block_bolt_n*64);//��������ģ�Ϳռ�����˨װ����Ϣ����
		buf.Offset((indexId-1)*92);	//������ǰ������ʶָ��ļ�¼
		assembly.bInBlockSpace=false;
		assembly.wBlockIndexId=0;
	}
	else
	{
		buf.Offset((indexId-1)*64);
		assembly.bInBlockSpace=true;
	}
	//��������
	buf.ReadByte(&assembly.cSeriesId);
	buf.ReadWord(&assembly.wIndexId);
	buf.ReadFloat(&assembly.grade);
	//��������
	buf.ReadPoint(assembly.origin);
	buf.ReadPoint(assembly.work_norm);
	buf.ReadWord(&assembly.wL0);
	buf.ReadByte(&assembly.cPropFlag);
	buf.ReadByte(&assembly.cDianQuanN);
	buf.ReadByte(&assembly.cDianQuanThick);
	buf.ReadWord(&assembly.wDianQuanOffset);
	if(!bTowerSpace)	//�����ռ�����˨װ������Ӧ�Ĳ���������ʶ
		buf.ReadWord(&assembly.wBlockIndexId);
	else //if(bTowerSpace)
	{					//����ģ�Ϳռ�����˨װ������Ӧ�Ĳ���������ʶ
		buf.ReadByte(&assembly.cStatFlag);
		buf.ReadDword(&assembly.dwSeg);
		buf.ReadByte(&assembly.cLegQuad);
		buf.Read(&assembly.cfgword,24);
		if(assembly.cStatFlag&0x80)	//��˨ͬʱ��������κţ��κ�ͳ�Ʒ�Χ���ַ�����ʽ�洢�ں��������ֽ���ָ��ַ��
		{
			buf.SeekPosition(AddrGtoL(assembly.dwSeg));
			buf.ReadString(assembly.statSegStr,50);
		}
	}
	return assembly;
}
CPartAssemblySection CAssembleSection::PartSection()
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD block_assembly_n,size;
	buf.ReadDword(&block_assembly_n);
	buf.Offset(block_assembly_n*128);
	buf.ReadDword(&size);
	buf.Offset(size);	//������˨װ����
	buf.ReadDword(&size);
	return CPartAssemblySection(buf.GetCursorBuffer(),size);
}
DWORD CPartAssemblySection::AssemblyCount(bool bTowerSpace/*=true*/)
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD assemble_n;
	if(bTowerSpace)
		buf.Offset(4);
	buf.ReadDword(&assemble_n);
	return assemble_n;
}
PART_ASSEMBLY CPartAssemblySection::GetAssemblyAt(int indexId,bool bTowerSpace/*=true*/)
{
	CBuffer buf(BufferPtr(),BufferLength());
	DWORD block_part_n,tower_part_n,rod_n;
	buf.ReadDword(&block_part_n);
	buf.ReadDword(&tower_part_n);
	if(CompareVersion(m_sVersion,"1.1")>=0)
		buf.ReadDword(&rod_n);	//�����˼���������

	PART_ASSEMBLY assembly;
	if(bTowerSpace)
	{
		assembly.bInBlockSpace=false;
		assembly.wBlockIndexId=0;
		if(CompareVersion(m_sVersion,"1.1")>=0)
		{	//���Ӽ��ߴ洢λ��4B����λӰ���洢λ��4B wjh-2016.1.18
			buf.Offset(block_part_n*110);	//��������ģ�Ϳռ��й���װ����Ϣ����
			buf.Offset((indexId-1)*133);	//������ǰ������ʶָ��ļ�¼
		}
		else
		{
			buf.Offset(block_part_n*102);	//��������ģ�Ϳռ��й���װ����Ϣ����
			buf.Offset((indexId-1)*125);	//������ǰ������ʶָ��ļ�¼
		}
		buf.ReadDword(&assembly.dwIndexId);
		buf.ReadByte(&assembly.cLegQuad);
		buf.Read(&assembly.cfgword,24);
	}
	else
	{
		if(CompareVersion(m_sVersion,"1.1")>=0)
			buf.Offset((indexId-1)*110);	//������ǰ������ʶָ��ļ�¼
		else
			buf.Offset((indexId-1)*102);	//������ǰ������ʶָ��ļ�¼
		assembly.bInBlockSpace=true;
		assembly.cLegQuad=0;
		buf.ReadDword(&assembly.dwIndexId);
		buf.ReadWord(&assembly.wBlockIndexId);
	}
	buf.ReadPoint(assembly.acs.origin);
	buf.ReadPoint(assembly.acs.axis_x);
	buf.ReadPoint(assembly.acs.axis_y);
	buf.ReadPoint(assembly.acs.axis_z);
	//��ȡװ���¼��˨����Ϣ��ַ
	if(CompareVersion(m_sVersion,"1.1")>=0)
	{
		DWORD addrHoleInfo=0;
		buf.ReadDword(&addrHoleInfo);
		/*if(addrHoleInfo>0)
		{	//��ȡ������Ϣ
			buf.SeekPosition(AddrGtoL(addrHoleInfo));
			DWORD size;
			buf.ReadDword(&size);
			assembly.hashBoltIndexByHoleId.Empty();
			for(DWORD i=0;i<size;i++)
			{
				DWORD dwBoltIndex=0,dwHoleId=0;
				buf.ReadDword(&dwHoleId);
				buf.ReadDword(&dwBoltIndex);
				assembly.hashBoltIndexByHoleId.SetValue(dwHoleId,dwBoltIndex);
			}
		}*/
		//��ȡ�˼���������
		if(assembly.dwAddrBriefLine>0)
		{
			buf.SeekPosition(AddrGtoL(assembly.dwAddrBriefLine));
			buf.ReadPoint(assembly.startPt);
			buf.ReadPoint(assembly.endPt);
			assembly.bIsRod=true;
		}
	}
	return assembly;
}

///////////////////////////////////////////////////////////////////////////////////////////////
CSolidTowerModel model;
CSolidTowerModel::CSolidTowerModel(void)
{
	m_iActiveModule=0;
	version=0;
	m_dwZeroAddrOffset=0;
	mcs.axis_x.Set(1,0,0);
	mcs.axis_y.Set(0,0,1);
	mcs.axis_z.Set(0,-1,0);
}

CSolidTowerModel::~CSolidTowerModel(void)
{
}
void CSolidTowerModel::InitBuffer(char* srcBuf, DWORD buf_size)
{
	ClearBuffer();
	Write(srcBuf,buf_size);
	CXhChar50 sDocType;
	SeekToBegin();
	ReadString(sDocType,50);
	if(strstr(sDocType,"Xerofox tower solid data media file")==NULL)
		throw "��Ԥ�ڵ��ļ���ʽ���ļ���ʧ��!";
	char* key=strtok(sDocType,"-");
	char* ver=strtok(NULL,"-");
	if(ver!=NULL)
		version=atof(ver);
	if(version>1.0)
		throw "���ļ��汾��̫�߻�̫��,����ֱ�Ӷ�ȡ���ļ�";
	ReadString(m_sTowerType,50);
	ReadPoint(mcs.axis_x);
	ReadPoint(mcs.axis_y);
	ReadPoint(mcs.axis_z);
	m_dwZeroAddrOffset=GetCursorPosition();
}
CModuleSection CSolidTowerModel::ModuleSection()
{
	DWORD pos,sect_len;
	SeekPosition(AddrLtoG(0));
	ReadDword(&pos);
	SeekPosition(pos);
	ReadDword(&sect_len);
	return CModuleSection(GetCursorBuffer(),sect_len);
}
CBlockSection CSolidTowerModel::BlockSection()
{
	DWORD pos,sect_len;
	SeekPosition(AddrLtoG(4));
	ReadDword(&pos);
	SeekPosition(pos);
	ReadDword(&sect_len);
	return CBlockSection(GetCursorPosition(),GetCursorBuffer(),sect_len);
}
CBoltSection CSolidTowerModel::BoltSection()
{
	DWORD pos,sect_len;
	SeekPosition(AddrLtoG(8));
	ReadDword(&pos);
	SeekPosition(pos);
	ReadDword(&sect_len);
	return CBoltSection(GetCursorPosition(),GetCursorBuffer(),sect_len);
}
CPartSection CSolidTowerModel::PartSection()
{
	DWORD pos,sect_len;
	SeekPosition(AddrLtoG(12));
	ReadDword(&pos);
	SeekPosition(pos);
	ReadDword(&sect_len);
	return CPartSection(GetCursorPosition(),GetCursorBuffer(),sect_len);
}
CAssembleSection CSolidTowerModel::AssembleSection()
{
	DWORD pos,sect_len;
	SeekPosition(AddrLtoG(16));
	ReadDword(&pos);
	SeekPosition(pos);
	ReadDword(&sect_len);
	return CAssembleSection(GetCursorBuffer(),sect_len);
}
