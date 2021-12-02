// Fiat LuxDoc.cpp : implementation of the CFiatLuxDoc class
//

#include "stdafx.h"
#include "Fiat Lux.h"
#include "math.h"
#include "Fiat LuxDoc.h"
#include "Progess.h"
#include <mmsystem.h>
#include "info.h"

#include <time.h>
#include <stdio.h>
#include <fstream.h>






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAXSURF 1024



static void CALLBACK  beginCallback(GLenum type);


/////////////////////////////////////////////////////////////////////////////
// CFiatLuxDoc

IMPLEMENT_DYNCREATE(CFiatLuxDoc, CDocument)

BEGIN_MESSAGE_MAP(CFiatLuxDoc, CDocument)
	//{{AFX_MSG_MAP(CFiatLuxDoc)
	ON_UPDATE_COMMAND_UI(ID_TB_SOLID, OnUpdateTbSolid)
	ON_UPDATE_COMMAND_UI(ID_TB_Smooth, OnUpdateTBSmooth)
	ON_UPDATE_COMMAND_UI(ID_TB_Flat, OnUpdateTBFlat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxDoc construction/destruction

CFiatLuxDoc::CFiatLuxDoc()
{
/*
	glEnable(GL_LIGHT0);
	
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glCullFace(GL_BACK);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_AUTO_NORMAL);
//	GLfloat pos[] = { 0,0,5.0, 0.0};
//	glLightfv(GL_LIGHT1, GL_POSITION, pos);
*/

	
	
//	m_Zoom = 1;
	m_xRotate = 0;
	m_yRotate = 180;
	m_xlight_trans = 0.2;
	m_ylight_trans = 0.2;
//	timeinit=0;
	for (int i=0;i<3;i++)
	{
		Light_color[i] = 1.0f;
		mat_ambient[i] = 0.02f;
		mat_diffuse[i] = 0.8f;
		mat_specular[i] = 0.5f;
		bkg_color[i] = 0.0f;
	}
	Light_color[3] = 1.0f;
	mat_ambient[3] = 1.0f;
	mat_diffuse[3] = 1.0f;
	mat_specular[3] = 1.0f;

	mat_shininess = 80;
	Init_flag = 0x0FFF;
	TR_flag = FALSE;
	Lighting_flag = 1;
	MyModel.num_surf = 0;
	MyModel.num_vert = 0;
	MyModel.num_tri = 0;
	MyModel.num_quad = 0;
	MyModel.num_poly = 0;
	MyModel.current_poly = 0;
	MyModel.current_tri = 0;
	MyModel.current_vtx = 0;
	MyModel.num_tess_tri = 0;

	FacesCulling = TRUE;
	ShowFPS = FALSE;
	TwoLights = TRUE;

	UpdateColours();	

	Init_Light_Obj();

	
}

CFiatLuxDoc::~CFiatLuxDoc()
{
}

BOOL CFiatLuxDoc::OnNewDocument()
{
	

//	glNewList(Disp_list, GL_COMPILE);
//	glEndList();
	//m_Zoom = 1;
	m_xRotate = 0;
	m_yRotate = 180;
	m_xlight_trans = 0.2;
	m_ylight_trans = 0.2;
	MyModel.num_tri = 0;
	MyModel.num_quad = 0;
	MyModel.num_vert = 0;
	MyModel.num_poly = 0;
	MyModel.num_tess_tri = 0;
	Init_flag = 0x0FFF;

/*	//FPS init
	timeinit=0;
	frame=0;
	frame2=0;*/

	m_DocPath = "init";
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFiatLuxDoc serialization

void CFiatLuxDoc::Serialize(CArchive& ar)
{	
	
	if (ar.IsStoring())
	{

	}
	else
	{
		CFile* fp = ar.GetFile();
	
		if ( strcmp( get_ID4(fp), "FORM" ) ) 
		{
			AfxMessageBox("Unknown file format", 0,1);
			
			
		}
		else 
		{

			m_pModeless = new CProgess();
			m_pModeless->Create();
			m_pModeless->SetActiveWindow();
			(m_pModeless->m_Progress).SetRange(0, 9);
			free_mem();
			if (read_LWOB(fp))
			{
				(m_pModeless->m_Progress).SetPos(6);
				m_pModeless->SetWindowText("Loading object: tessellating polygons");

			
				tessellatePolys();
				MyModel.num_tri = MyModel.current_tri;

				(m_pModeless->m_Progress).SetPos(7);
				m_pModeless->SetWindowText("Loading object: Calculating normals");
				// Compute normals
				compute_normals(&MyModel);

				Rescale_normal(&MyModel, m_Zoom);

				if (TR_flag){


				(m_pModeless->m_Progress).SetPos(8);
				m_pModeless->SetWindowText("Loading object: Building display lists");


					Dump_disp_list();
					build_disp_list();
				}
			
				(m_pModeless->m_Progress).SetPos(9);
			
				delete m_pModeless;

				
			}
	/*		else {
			//	delete m_pModeless;
				AfxMessageBox("Why does it crashes ?");
			}*/

	
		}

	}
	
}

// Get an ID tag data type
char* CFiatLuxDoc::get_ID4(CFile* fp)
{

	char buf[5] = {' ',' ',' ',' ','\0'};
	UINT pb = fp->Read( buf, 4 );
	return (buf);

}

CString CFiatLuxDoc::get_S0(CFile* fp)
{
	char buf[256];
	int i = 0;

	fp->Read(&buf[i],1);
	while (buf[i] != '\0')
	{ 
		i++;
		fp->Read(&buf[i],1);
		
	}
	buf[++i] = '\0';


	return (buf);

}


// Get an I4 data type (signed 4 bytes integer)
int CFiatLuxDoc::get_I4(CFile* fp)
{
	int    temp;
  	char buf[4];
	char* inv = (char*) &temp;

	// read raw data from file
	fp->Read(buf, 4 );

	// data must be reversed in order to be used on Intel CPU
	inv[3] = buf[0];
	inv[2] = buf[1];
	inv[1] = buf[2];
	inv[0] = buf[3];

    return ( temp );
}

// Get an I4 data type (signed 4 bytes integer) from a buffer
int CFiatLuxDoc::mem_get_I4(char* buf, int i)
{
	int    temp;
  	char* inv = (char*) &temp;



	// data must be reversed in order to be used on Intel CPU
	inv[3] = buf[i];
	inv[2] = buf[i+1];
	inv[1] = buf[i+2];
	inv[0] = buf[i+3];

    return ( temp );
}

// Get an U4 data type (unsigned 4 bytes integer)
unsigned int CFiatLuxDoc::get_U4(CFile* fp)
{
	unsigned int    temp;
  	unsigned char buf[4];
	unsigned char* inv = (unsigned char*) &temp;

	// read raw data from file
	fp->Read(buf, 4 );

	// data must be reversed in order to be used on Intel CPU
	inv[3] = buf[0];
	inv[2] = buf[1];
	inv[1] = buf[2];
	inv[0] = buf[3];

    return ( temp );
}


// Get an U4 data type (unsigned 4 bytes integer)
unsigned int CFiatLuxDoc::mem_get_U4(char* buf, int i)
{
	unsigned int    temp;
  	unsigned char* inv = (unsigned char*) &temp;

	
	// data must be reversed in order to be used on Intel CPU
	inv[3] = buf[i];
	inv[2] = buf[i+1];
	inv[1] = buf[i+2];
	inv[0] = buf[i+3];

    return ( temp );
}

// Get an U2 data type (unsigned 2 bytes integer)
unsigned short int CFiatLuxDoc::get_U2(CFile* fp)
{
	unsigned short int temp;
	unsigned char buf[2];
	unsigned char * inv = (unsigned char *) &temp;

	// read raw data from file
	fp->Read( buf, 2 );

	// data must be reversed in order to be used on Intel CPU
	inv[1] = buf[0];
	inv[0] = buf[1];
	
	return ( temp );
	
}

unsigned char  CFiatLuxDoc::get_U1(CFile* fp)
{
//	unsigned short int temp;
	unsigned char buf[1];
//	unsigned char * inv = (unsigned char *) &temp;

	// read raw data from file
	fp->Read( buf, 1 );

		
	return ( buf[0] );
	
}


// Get an U2 data type (unsigned 2 bytes integer)
unsigned short int CFiatLuxDoc::mem_get_U2(char* buf,int i)
{
	unsigned short int temp;
	unsigned char * inv = (unsigned char *) &temp;
//	char str[50];
/*f (i > sizeof(buf)){
	//	return 0;
	//fxMessageBox(itoa(sizeof(&buf),str,10),1,1);

	}
*/

	// data must be reversed in order to be used on Intel CPU
	inv[1] = buf[i];
	inv[0] = buf[i+1];
	
	return ( temp );
	
}

short int CFiatLuxDoc::get_I2(CFile* fp)
{
	short int temp;
	char buf[2];
	char * inv = (char *) &temp;

	// read raw data from file
	fp->Read( buf, 2 );

	// data must be reversed in order to be used on Intel CPU
	inv[1] = buf[0];
	inv[0] = buf[1];
	
	return ( temp );
	
}

short int CFiatLuxDoc::mem_get_I2(char* buf, int i)
{
	short int temp;
	char * inv = (char *) &temp;

	

	// data must be reversed in order to be used on Intel CPU
	inv[1] = buf[i];
	inv[0] = buf[i+1];
	
	return ( temp );
	
}

// Get a F4 (4 bytes float) from a file
float CFiatLuxDoc::get_F4(CFile* fp)
{
	float  temp;
    char buf[4];
	char * inv = (char *) &temp;
	
	// read raw data from file
	fp->Read( buf, 4 );
	
	// data must be reversed in order to be used on Intel CPU
    inv[3] = buf[0];
	inv[2] = buf[1];
	inv[1] = buf[2];
	inv[0] = buf[3];

    return ( temp );
}

// Get a F4 (4 bytes float) from a buffer
float CFiatLuxDoc::mem_get_F4(char* buf, int i)
{
	float  temp;
  	char * inv = (char *) &temp;

	
	// data must be reversed in order to be used on Intel CPU
    inv[3] = buf[i];
	inv[2] = buf[i+1];
	inv[1] = buf[i+2];
	inv[0] = buf[i+3];

    return ( temp );
}


// find data chunks
int CFiatLuxDoc::find_chunk(CFile* fp, char * chunk, BOOL FromStart)
{
	DWORD filelen=0;
	DWORD br = 0;
	char  disk_temp[5]={ ' ', ' ', ' ', ' ', '\0' };
	char* mystr ="init";
	

	
		
	if (FromStart){
		fp->SeekToBegin();
	}
	
	filelen = fp->GetLength();
	br = fp->GetPosition();
	 {
     do
     {
        do
        {
           br += fp->Read( disk_temp,1);
        }
        while ( disk_temp[0] != chunk[0] && br < filelen );

        while ( disk_temp[0] == chunk[0] )
        {
           br += fp->Read( disk_temp,1);
           if ( disk_temp[0] == chunk[1] && br < filelen  )
           {
              br += fp->Read( disk_temp,1);
              if ( disk_temp[0] == chunk[2] && br < filelen  )
              {
                 br += fp->Read( disk_temp,1);
                 if ( disk_temp[0] == chunk[3] && br < filelen  )
                    return 1;
              }
           }
        }
    } while ( br < filelen );
    return (0);
 }

}

// Read data from a LWO file
int CFiatLuxDoc::read_LWOB(CFile* fp)
{
	int size_v,size_p,i,j,temp_nv;
	maxsize = -1;
	int ti = 0,qi = 0,pi = 0;
//	unsigned short int vertex_id;
	char* buffer;
	DWORD srfs_pos;
	int k=1, f = 0;


	m_Zoom = 1.0;
	scale = 0.07f ;
	m_ZoomNorm = 1.0;

	
	// init
	MyModel.num_tri = 0;
	MyModel.num_quad = 0;
	MyModel.num_poly = 0;
	MyModel.num_poly = 0;
	MyModel.num_tess_tri = 0;
	MyModel.current_tri = 0;
	MyModel.current_vtx = 0;
	MyModel.current_poly = 0;


//	nt_supp = 0;
	center[1] = center[2] = center[0] = 0;
	max[1] = max[2] = max[0] = -99999999.0f;
	min[1] = min[2] = min[0] = 99999999.0f;
	MyModel.num_surf = 1;


	//update progress bar
	(m_pModeless->m_Progress).SetPos(1);
	m_pModeless->SetWindowText("Loading object: Collecting surfaces names");
	// Find number of surfaces 
	if (!find_chunk(fp, "SRFS", TRUE)) AfxMessageBox("Error reading LWO: Can't find surface names", 1, 1);
	else {
			srfs_pos = fp->GetPosition();
			int tmp_size = get_U4(fp);
			
			buffer = (char*)malloc(tmp_size*sizeof(char)); //buffer to read polygons
						
			fp->Read(buffer,tmp_size);
			for (i = 0;i<tmp_size;i++)
			{
				if (buffer[i] == '\0'){
					MyModel.num_surf++;
				
						if (buffer[i+1] == '\0') i++;
				}
			}
	}



	MyModel.surface = new SURFACE[MyModel.num_surf];


	// Init my debug surface
	MyModel.surface[0].name = "debug";
	MyModel.surface[0].colorRGBA[0] = 1.0;
	MyModel.surface[0].colorRGBA[1] = 0.0;
	MyModel.surface[0].colorRGBA[2] = 0.0;
	MyModel.surface[0].colorRGBA[3] = 1.0;	


	fp->Seek(srfs_pos,CFile::begin);
	get_U4(fp);
	for (k=1;k<MyModel.num_surf;k++)
	{				
		MyModel.surface[k].name = (get_S0(fp));
		if (get_U1(fp) != '\0') fp->Seek(-1,CFile::current);
	}

	
	

	//update progress bar
	(m_pModeless->m_Progress).SetPos(2);
	m_pModeless->SetWindowText("Loading object: Getting vertices data");


	// Create vertices list

	if (!find_chunk(fp, "PNTS", TRUE))
	{
		AfxMessageBox("Error reading LWO: Can't find vertices", 1, 1);
		delete m_pModeless;
		return(0);
	}
	
	
	


	size_v = get_U4(fp);

	buffer = (char*)malloc(size_v*sizeof(char));
	fp->Read(buffer, size_v);

	MyModel.num_vert = size_v / (sizeof(float)*3);

	MyModel.vertexList = new VERTEX[MyModel.num_vert];
	
	int zorg = 0;

	for (i=0;i < MyModel.num_vert;i++)
	
	{
		for (j=0;j<3;j++){

			MyModel.vertexList[i].coord[j] = mem_get_F4(buffer, zorg*sizeof(float));
		
			if (MyModel.vertexList[i].coord[j] > max[j]) max[j] = MyModel.vertexList[i].coord[j];
			if (MyModel.vertexList[i].coord[j] < min[j]) min[j] = MyModel.vertexList[i].coord[j];
			zorg++;
		}
		
	}
	

	free(buffer);
	float size[3];

	for (i=0;i < 3;i++)
	{
		//center[i] = center[i] / (float)MyModel.num_vert;
		size[i] = max[i] - min [i];
		center[i] = max[i] - (size[i]/2);
		if (size[i] > maxsize) maxsize = size[i];
		
	}
	



	for (i = 0; i < MyModel.num_vert; i++) {
 
		MyModel.vertexList[i].coord[0] -= center[0];
		MyModel.vertexList[i].coord[1] -= center[1];
		MyModel.vertexList[i].coord[2] -= center[2];

		MyModel.vertexList[i].coord[0] *= 1.8f / maxsize;
		MyModel.vertexList[i].coord[1] *= 1.8f / maxsize;
		MyModel.vertexList[i].coord[2] *= 1.8f / maxsize;


	}

//	char str[20];
//	AfxMessageBox(gcvt(maxsize,4,str));


	//update progress bar
	(m_pModeless->m_Progress).SetPos(3);
	 m_pModeless->SetWindowText("Loading object: Allocating memory for data structure");



// Cycle through the polygon chunk to determine the amount of mem. needed for each
// polygon list (triangles, quads and others)
	if (!find_chunk(fp, "POLS", TRUE))
	{
		AfxMessageBox("Error reading LWO: Can't find polygons infos\nThe object you are trying to load might be defined by NURBS\nFiat Lux does not support NURBS at the moment, sorry.", 1, 1);
		delete m_pModeless;
		return(0);
	}

	

	size_p = get_U4(fp); // get the size in byte of the chunk

	buffer = (char*)malloc(size_p*sizeof(char)); //buffer to read polygons

	fp->Read(buffer, size_p );

	i = 0;
	while (i < size_p)
	{
		temp_nv = mem_get_U2(buffer,i); // get nb of vertices of this poly
		i+=2;
		if (temp_nv == 3)
		{
			MyModel.num_tri++;			// found a triangle
			i += 6;
		}
		else if (temp_nv == 4)
			{
				MyModel.num_quad++;		// found a quad
				i += 8;
			}
			
			else 
			{	
			//	if (temp_nv > MAXPOINT){
			//		AfxMessageBox("Error: polygon has to many vertices");
			//		temp_nv = 5;
			//		return(0);
			//	}
				
				if ((temp_nv > 3) && (temp_nv < MAXPOINT)){
					MyModel.num_tess_tri+=(temp_nv-2);
					MyModel.num_poly++;
				}
				i += temp_nv*2;
				
			}

	
	i+=2;

	}

	

	MyModel.triangle = new TRIANGLE[MyModel.num_tri + MyModel.num_tess_tri];
	MyModel.quad = new QUAD[MyModel.num_quad];
	MyModel.poly = new POLY[MyModel.num_poly];



	//update progress bar
	(m_pModeless->m_Progress).SetPos(4);
	m_pModeless->SetWindowText("Loading object: Collecting polygons data");


	i = 0;
	

	while (i < size_p)
	{
		temp_nv = mem_get_U2(buffer,i); // get nb of vertices of this poly
		i+=2;
		if (temp_nv == 3)
		{
			
			for (j=0;j<3;j++) {

				MyModel.triangle[ti].vertex[j] = &MyModel.vertexList[mem_get_U2(buffer,i)];
				i += 2;
			}

			MyModel.triangle[ti].surf_Ref = mem_get_I2(buffer,i);
			i += 2;
			ti++;

	

		}
		else if (temp_nv == 4)
		{
			
			for (j=0;j<4;j++){

				MyModel.quad[qi].vertex[j] = &MyModel.vertexList[mem_get_U2(buffer,i)];
				i += 2;
			}

			
			MyModel.quad[qi].surf_Ref = mem_get_I2(buffer,i);
			i += 2;
			qi++;
	
		}
			
		else 
		{
		
			if ((temp_nv > 3) && (temp_nv < MAXPOINT)){
			
				MyModel.poly[pi].num_pVertex = temp_nv;
				for (j=0;j<(temp_nv);j++){

					MyModel.poly[pi].vertex[j] = &MyModel.vertexList[mem_get_U2(buffer,i)];
					i += 2;	
				}

				MyModel.poly[pi].surf_Ref = mem_get_I2(buffer,i);
				i+=2;
				

				/*-----------------------------/
				/  create triangles from polys /
				/-----------------------------

				for (j=0;j<(temp_nv-2);j++){

					MyModel.triangle[ti].vertex[0] = MyModel.poly[pi].vertex[0];
					MyModel.triangle[ti].vertex[1] = MyModel.poly[pi].vertex[j+1];
					MyModel.triangle[ti].vertex[2] = MyModel.poly[pi].vertex[j+2];

					MyModel.triangle[ti].surf_Ref = MyModel.poly[pi].surf_Ref;
					ti++;

				}
				/*--------------------------------------*/

				pi++;

			} 
			else i+= (temp_nv*2) + 2;



		}

	}

	free(buffer);



	//update progress bar
	(m_pModeless->m_Progress).SetPos(5);
	m_pModeless->SetWindowText("Loading object: Collecting surfaces param.");


	CString tmp_str;

	int size_surf = 0;
	
	for (i=1;i < MyModel.num_surf;i++)
	{
		MyModel.surface[i].colorRGBA[0] = 0.9f;
		MyModel.surface[i].colorRGBA[1] = 0.9f;
		MyModel.surface[i].colorRGBA[2] = 0.9f;
	}
	
	i = 1;

	while (find_chunk(fp, "SURF", FALSE))
	{
			
		get_U4(fp);
			tmp_str = get_S0(fp);
			if (get_U1(fp) != '\0') fp->Seek(-1,CFile::current);
			for (k=0;k<MyModel.num_surf;k++)
			{
				if (MyModel.surface[k].name == tmp_str) 
				{
				
			
					i=k;
					break;
				}
			}

			if (get_U1(fp) != '\0') fp->Seek(5,CFile::current);
			else fp->Seek(6,CFile::current);
			MyModel.surface[i].colorRGBA[0] = (float)get_U1(fp) / 0xFF;
			MyModel.surface[i].colorRGBA[1] = (float)get_U1(fp) / 0xFF;
			MyModel.surface[i].colorRGBA[2] = (float)get_U1(fp) / 0xFF;
			MyModel.surface[i].colorRGBA[3] = 1.0;
		
			
	}		
	

//	AfxMessageBox(MyModel.surface[0].name);
	//update progress bar
	

	return 1;
}

void CFiatLuxDoc::disp_infos()
{
	
	CInfo Info_Box;
	char str2[256], str[1024];
	CString surf_str, glStr = "GL: ", gluStr = " / GLU: " ;
	int k;
	
	


	
	for (k=1;k<MyModel.num_surf;k++){
	Info_Box.m_surf += MyModel.surface[k].name;
	Info_Box.m_surf += "\x0D\x0A";
	Info_Box.m_surf += "R:";
	Info_Box.m_surf += itoa((int)(MyModel.surface[k].colorRGBA[0]*255),str2,10);
	Info_Box.m_surf += "\x09";
	Info_Box.m_surf += "G:";
	Info_Box.m_surf += itoa((int)(MyModel.surface[k].colorRGBA[1]*255),str2,10);
	Info_Box.m_surf += "\x09";
	Info_Box.m_surf += "B:";
	Info_Box.m_surf += itoa((int)(MyModel.surface[k].colorRGBA[2]*255),str2,10);

	Info_Box.m_surf += "\x0D\x0A";
//	Info_Box.m_surf += "\x0A";

	
 				
	}


	Info_Box.m_vertices = (CString)itoa(MyModel.num_vert,str,10);
	Info_Box.m_quads = (CString)itoa(MyModel.num_quad,str,10);
	Info_Box.m_triangles = (CString)itoa(MyModel.num_tri,str,10);
	Info_Box.m_tt = (CString)itoa(MyModel.num_poly,str,10) + " (" + (CString)itoa(MyModel.current_tri,str,10) + " triangles)";
//	Info_Box.m_tt = (CString)itoa(MyModel.num_tri + MyModel.num_tess_tri,str,10) + " (" + (CString)itoa(MyModel.current_tri,str,10) + " triangles)";
	Info_Box.m_surfaces = (CString)itoa(MyModel.num_surf,str,10);

	
	
	
	Info_Box.m_gl_version = glStr + (CString)glGetString(GL_VERSION) + gluStr + (CString)gluGetString(GLU_VERSION);
	Info_Box.m_gl_vendor = (char*)glGetString(GL_VENDOR);
	Info_Box.m_gl_ext = (char*)glGetString(GL_EXTENSIONS);
	Info_Box.m_gl_render = (char*)glGetString(GL_RENDERER);

//	Info_Box.m_surf = lpszTrouble;
	
//	AfxMessageBox(Info_Box.m_surf);
	
	if (Info_Box.DoModal() == IDOK)
	{
				
	
	}
	
	

}

void CFiatLuxDoc::Dump_disp_list()
{

	if (glIsList(Disp_list)) glDeleteLists(Disp_list, 1);


}




///////////////////////////////////////////////////////////////////////////
// Build the display list from file data

int CFiatLuxDoc::build_disp_list()
{

/*	CProgess* DLProgress;
	DLProgress = new CProgess();
	DLProgress->Create();
	DLProgress->SetWindowText("Building display list");
	DLProgress->SetActiveWindow();
	(DLProgress->m_Progress).SetRange(0, 2);
		
	*/
	


	if (glIsList(Disp_list)){
		glDeleteLists(Disp_list, 1);
	}
	
	Disp_list = glGenLists(1);

//	(DLProgress->m_Progress).SetPos(1);


	

	switch (Lighting_flag) {
							
		case 1: //Smooth shading diplay
			
			glNewList(Disp_list, GL_COMPILE);
	
			DrawSmoothObject();

			glEndList();
			
			break;
		
		case 2: // Flat shading diplay

			glNewList(Disp_list, GL_COMPILE);
	
			DrawFlatObject();

			glEndList();
			
		} 


//	(DLProgress->m_Progress).SetPos(2);
//	delete DLProgress;

 
	return 1;

}

void CFiatLuxDoc::Init_Light_Obj()
{

	int i,k;
	float vData[][3] = {

		{1.13514e-05f,0.0970332f,0.00287177f},{0.015427f,0.095059f,0.00287177f},{-0.0154043f,0.095059f,0.00287177f},
{-0.0148791f,0.095059f,0.00545718f},{-0.013339f,0.095059f,0.00786639f},{-0.0108892f,0.095059f,0.00993523f},
{-0.00769649f,0.095059f,0.0115227f},{-0.00397852f,0.095059f,0.0125206f},{1.13514e-05f,0.095059f,0.012861f},
{0.00400122f,0.095059f,0.0125206f},{0.00771919f,0.095059f,0.0115227f},{0.0109119f,0.095059f,0.00993523f},
{0.0133617f,0.095059f,0.00786639f},{0.0149018f,0.095059f,0.00545718f},{0.0297922f,0.0892709f,0.00287177f},
{-0.0297695f,0.0892709f,0.00287177f},{-0.0287547f,0.0892709f,0.00786639f},{-0.0257796f,0.0892709f,0.0125206f},
{-0.0210469f,0.0892709f,0.0165173f},{-0.0148791f,0.0892709f,0.0195841f},{-0.00769649f,0.0892709f,0.0215119f},
{1.13514e-05f,0.0892709f,0.0221695f},{0.00771919f,0.0892709f,0.0215119f},{0.0149018f,0.0892709f,0.0195841f},
{0.0210696f,0.0892709f,0.0165173f},{0.0258023f,0.0892709f,0.0125206f},{0.0287774f,0.0892709f,0.00786639f},
{0.0421278f,0.0800634f,0.00287177f},{-0.0421051f,0.0800634f,0.00287177f},{-0.04067f,0.0800634f,0.00993523f},
{-0.0364625f,0.0800634f,0.0165173f},{-0.0297695f,0.0800634f,0.0221695f},{-0.0210469f,0.0800634f,0.0265065f},
{-0.0108892f,0.0800634f,0.0292329f},{1.13514e-05f,0.0800634f,0.0301629f},{0.0109119f,0.0800634f,0.0292329f},
{0.0210696f,0.0800634f,0.0265065f},{0.0297922f,0.0800634f,0.0221695f},{0.0364853f,0.0800634f,0.0165173f},
{0.0406927f,0.0800634f,0.00993523f},{0.0515932f,0.068064f,0.00287177f},{-0.0515705f,0.068064f,0.00287177f},
{-0.0498129f,0.068064f,0.0115227f},{-0.0446599f,0.068064f,0.0195841f},{-0.0364625f,0.068064f,0.0265065f},
{-0.0257796f,0.068064f,0.0318183f},{-0.013339f,0.068064f,0.0351575f},{1.13514e-05f,0.068064f,0.0362964f},
{0.0133617f,0.068064f,0.0351575f},{0.0258023f,0.068064f,0.0318183f},{0.0364853f,0.068064f,0.0265065f},
{0.0446826f,0.068064f,0.0195841f},{0.0498356f,0.068064f,0.0115227f},{0.0575435f,0.0540903f,0.00287177f},
{-0.0575208f,0.0540903f,0.00287177f},{-0.0555604f,0.0540903f,0.0125206f},{-0.0498129f,0.0540903f,0.0215119f},
{-0.04067f,0.0540903f,0.0292329f},{-0.0287547f,0.0540903f,0.0351575f},{-0.0148791f,0.0540903f,0.0388818f},
{1.13514e-05f,0.0540903f,0.0401521f},{0.0149018f,0.0540903f,0.0388818f},{0.0287774f,0.0540903f,0.0351575f},
{0.0406927f,0.0540903f,0.0292329f},{0.0498356f,0.0540903f,0.0215119f},{0.0555831f,0.0540903f,0.0125206f},
{0.059573f,0.0390948f,0.00287177f},{-0.0595503f,0.0390948f,0.00287177f},{-0.0575208f,0.0390948f,0.012861f},
{-0.0515705f,0.0390948f,0.0221695f},{-0.0421051f,0.0390948f,0.0301629f},{-0.0297695f,0.0390948f,0.0362964f},
{-0.0154043f,0.0390948f,0.0401521f},{1.13514e-05f,0.0390948f,0.0414672f},{0.015427f,0.0390948f,0.0401521f},
{0.0297922f,0.0390948f,0.0362964f},{0.0421278f,0.0390948f,0.0301629f},{0.0515932f,0.0390948f,0.0221695f},
{0.0575435f,0.0390948f,0.012861f},{0.0543257f,0.0114309f,0.00287177f},{-0.0549853f,0.0114309f,0.00287177f},
{-0.0531229f,0.0114309f,0.0125206f},{-0.0476628f,0.0114309f,0.0215119f},{-0.038977f,0.0114309f,0.0292329f},
{-0.0276575f,0.0114309f,0.0351575f},{-0.0144756f,0.0114309f,0.0388818f},{-0.000329763f,0.0114309f,0.0401521f},
{0.0138161f,0.0114309f,0.0388818f},{0.026998f,0.0114309f,0.0351575f},{0.0383175f,0.0114309f,0.0292329f},
{0.0470033f,0.0114309f,0.0215119f},{0.0524634f,0.0114309f,0.0125206f},{0.046435f,-0.00672652f,0.00287177f},
{-0.0464123f,-0.00672652f,0.00287177f},{-0.0448305f,-0.00672652f,0.0115227f},{-0.0401927f,-0.00672652f,0.0195841f},
{-0.0328152f,-0.00672652f,0.0265065f},{-0.0232005f,-0.00672652f,0.0318183f},{-0.012004f,-0.00672652f,0.0351575f},
{1.13514e-05f,-0.00672652f,0.0362964f},{0.0120267f,-0.00672652f,0.0351575f},{0.0232232f,-0.00672652f,0.0318183f},
{0.0328379f,-0.00672652f,0.0265065f},{0.0402155f,-0.00672652f,0.0195841f},{0.0448532f,-0.00672652f,0.0115227f},
{0.0379161f,-0.0238406f,0.00287177f},{-0.0378934f,-0.0238406f,0.00287177f},{-0.0366019f,-0.0238406f,0.00993523f},
{-0.0328152f,-0.0238406f,0.0165173f},{-0.0267914f,-0.0238406f,0.0221695f},{-0.018941f,-0.0238406f,0.0265065f},
{-0.00979913f,-0.0238406f,0.0292329f},{1.13514e-05f,-0.0238406f,0.0301629f},{0.00982183f,-0.0238406f,0.0292329f},
{0.0189637f,-0.0238406f,0.0265065f},{0.0268141f,-0.0238406f,0.0221695f},{0.0328379f,-0.0238406f,0.0165173f},
{0.0366246f,-0.0238406f,0.00993523f},{0.0268141f,-0.05212f,0.00287177f},{-0.0267914f,-0.05212f,0.00287177f},
{-0.0258781f,-0.05212f,0.00786639f},{-0.0232005f,-0.05212f,0.0125206f},{-0.018941f,-0.05212f,0.0165173f},
{-0.01339f,-0.05212f,0.0195841f},{-0.00692571f,-0.05212f,0.0215119f},{1.13514e-05f,-0.05212f,0.0221695f},
{0.00694841f,-0.05212f,0.0215119f},{0.0134127f,-0.05212f,0.0195841f},{0.0189637f,-0.05212f,0.0165173f},
{0.0232232f,-0.05212f,0.0125206f},{0.0259008f,-0.05212f,0.00786639f}
};

	float vArrow1[][3] = {

		{-0.172797f,0.0320505f,-0.000287227f},{-0.109851f,-0.0311295f,-0.000287227f},{-0.172797f,-0.0311295f,-0.000287227f},
{-0.109851f,0.0320505f,-0.000287227f},{-0.26767f,0.000460502f,-0.000287227f},{-0.172797f,-0.0627195f,-0.000287227f},
{-0.172797f,0.0636405f,-0.000287227f},{-0.252154f,9.2317e-05f,0.00603077f},{-0.183211f,0.0367327f,0.00603077f},
{-0.183211f,0.0176455f,0.00603077f},{-0.123947f,0.0176455f,0.00603077f},{-0.123947f,-0.0167245f,0.00603077f},
{-0.183211f,-0.0167245f,0.00603077f},{-0.183211f,-0.038389f,0.00603077f},{0.0176455f,0.183211f,0.00603077f},
{0.0176455f,0.123947f,0.00603077f},{-0.0167245f,0.123947f,0.00603077f},{-0.0167245f,0.183211f,0.00603077f},
{-0.038389f,0.183211f,0.00603077f},{9.23168e-05f,0.252154f,0.00603077f},{0.0367327f,0.183211f,0.00603077f},
{-0.0627195f,0.172797f,-0.000287227f},{0.000460503f,0.26767f,-0.000287227f},{0.0636405f,0.172797f,-0.000287227f},
{0.0320505f,0.172797f,-0.000287227f},{0.0320505f,0.109851f,-0.000287227f},{-0.0311295f,0.109851f,-0.000287227f},
{-0.0311295f,0.172797f,-0.000287227f},{0.183211f,-0.0176455f,0.00603077f},{0.123947f,-0.0176455f,0.00603077f},
{0.123947f,0.0167245f,0.00603077f},{0.183211f,0.0167245f,0.00603077f},{0.183211f,0.038389f,0.00603077f},
{0.252154f,-9.23169e-05f,0.00603077f},{0.183211f,-0.0367327f,0.00603077f},{0.172797f,0.0627195f,-0.000287227f},
{0.26767f,-0.000460502f,-0.000287227f},{0.172797f,-0.0636405f,-0.000287227f},{0.172797f,-0.0320505f,-0.000287227f},
{0.109851f,-0.0320505f,-0.000287227f},{0.109851f,0.0311295f,-0.000287227f},{0.172797f,0.0311295f,-0.000287227f},
{-0.0176455f,-0.183211f,0.00603077f},{-0.0176455f,-0.123947f,0.00603077f},{0.0167245f,-0.123947f,0.00603077f},
{0.0167245f,-0.183211f,0.00603077f},{0.038389f,-0.183211f,0.00603077f},{-9.23168e-05f,-0.252154f,0.00603077f},
{-0.0367327f,-0.183211f,0.00603077f},{0.0627195f,-0.172797f,-0.000287227f},{-0.000460502f,-0.26767f,-0.000287227f},
{-0.0636405f,-0.172797f,-0.000287227f},{-0.0320505f,-0.172797f,-0.000287227f},{-0.0320505f,-0.109851f,-0.000287227f},
{0.0311295f,-0.109851f,-0.000287227f},{0.0311295f,-0.172797f,-0.000287227f}
};
	
	int pArrow1[][3] = {

	{47,46,45 }, {42,48,47 }, {45,42,47 }, {33,32,31 }, {28,34,33 },
	{31,28,33 }, {19,18,17 }, {14,20,19 }, {17,14,19 }, {7,13,12 },
	{9,8,7 }, {12,9,7 }, {45,44,43 }, {43,42,45 }, {46,47,50 }, {50,49,46 },
	{47,48,51 }, {51,50,47 }, {48,42,52 }, {52,51,48 }, {42,43,53 },
	{53,52,42 }, {43,44,54 }, {54,53,43 }, {44,45,55 }, {55,54,44 },
	{45,46,49 }, {49,55,45 }, {31,30,29 }, {29,28,31 }, {32,33,36 },
	{36,35,32 }, {33,34,37 }, {37,36,33 }, {34,28,38 }, {38,37,34 },
	{28,29,39 }, {39,38,28 }, {29,30,40 }, {40,39,29 }, {30,31,41 },
	{41,40,30 }, {31,32,35 }, {35,41,31 }, {17,16,15 }, {15,14,17 },
	{18,19,22 }, {22,21,18 }, {19,20,23 }, {23,22,19 }, {20,14,24 },
	{24,23,20 }, {14,15,25 }, {25,24,14 }, {15,16,26 }, {26,25,15 },
	{16,17,27 }, {27,26,16 }, {17,18,21 }, {21,27,17 }, {12,11,10 },
	{10,9,12 }, {13,7,4 }, {4,5,13 }, {7,8,6 }, {6,4,7 }, {8,9,0 },
	{0,6,8 }, {9,10,3 }, {3,0,9 }, {10,11,1 }, {1,3,10 }, {11,12,2 },
	{2,1,11 }, {12,13,5 }, {5,2,12 }

	};


	float vCyl[][3] = {
{0.0268141f,-0.05212f,0.00287177f},{-0.0267914f,-0.05212f,0.00287177f},{-0.0258781f,-0.05212f,0.00786639f},
{-0.0232005f,-0.05212f,0.0125206f},{-0.018941f,-0.05212f,0.0165173f},{-0.01339f,-0.05212f,0.0195841f},
{-0.00692571f,-0.05212f,0.0215119f},{1.13514e-05f,-0.05212f,0.0221695f},{0.00694841f,-0.05212f,0.0215119f},
{0.0134127f,-0.05212f,0.0195841f},{0.0189637f,-0.05212f,0.0165173f},{0.0232232f,-0.05212f,0.0125206f},
{0.0259008f,-0.05212f,0.00786639f},{-0.0266259f,-0.0852863f,0.00294338f},{-0.0257188f,-0.0852863f,0.00780368f},
{-0.0230577f,-0.0852863f,0.0125734f},{-0.0188241f,-0.0852863f,0.0165474f},{-0.0133073f,-0.0852863f,0.0195893f},
{-0.00688275f,-0.0852863f,0.0215136f},{1.13518e-05f,-0.0852863f,0.0222037f},{0.00690545f,-0.0852863f,0.0215136f},
{0.01333f,-0.0852863f,0.0195893f},{0.0188468f,-0.0852863f,0.0165474f},{0.0230804f,-0.0852863f,0.0125734f},
{0.0257415f,-0.0852863f,0.00780368f},{0.0266486f,-0.0852863f,0.00294338f},{1.13521e-05f,-0.0852863f,0.00294338f}
	};

	int pCyl[][3] = {

	{2,1,13 }, {13,14,2 }, {2,14,15 }, {3,2,15 }, {15,16,4 }, {3,15,4 },
	{16,17,5 }, {4,16,5 }, {17,18,6 }, {5,17,6 }, {18,19,7 }, {6,18,7 },
	{20,8,7 }, {7,19,20 }, {21,9,8 }, {8,20,21 }, {22,10,9 }, {9,21,22 },
	{23,11,10 }, {10,22,23 }, {23,24,12 }, {12,11,23 }, {25,0,12 },
	{12,24,25 }, {26,25,24 }, {26,24,23 }, {26,23,22 }, {26,22,21 },
	{26,21,20 }, {26,20,19 }, {26,19,18 }, {26,18,17 }, {26,17,16 },
	{26,16,15 }, {26,15,14 }, {26,14,13 }
	};



//////////
	int pData[][3] = {
		
	{2,3,0 }, {3,4,0 }, {4,5,0 }, {5,6,0 }, {6,7,0 }, {7,8,0 }, {8,9,0 },
	{9,10,0 }, {10,11,0 }, {11,12,0 }, {12,13,0 }, {13,1,0 }, {2,15,16 },
	{16,3,2 }, {3,16,17 }, {17,4,3 }, {4,17,18 }, {18,5,4 }, {5,18,19 },
	{19,6,5 }, {6,19,20 }, {20,7,6 }, {7,20,21 }, {21,8,7 }, {9,8,21 },
	{22,9,21 }, {10,9,22 }, {23,10,22 }, {11,10,23 }, {24,11,23 },
	{12,11,24 }, {25,12,24 }, {13,12,25 }, {26,13,25 }, {1,13,26 },
	{14,1,26 }, {15,28,29 }, {29,16,15 }, {16,29,30 }, {30,17,16 },
	{17,30,31 }, {31,18,17 }, {18,31,32 }, {32,19,18 }, {19,32,33 },
	{33,20,19 }, {20,33,34 }, {34,21,20 }, {22,21,34 }, {35,22,34 },
	{23,22,35 }, {36,23,35 }, {24,23,36 }, {37,24,36 }, {25,24,37 },
	{38,25,37 }, {26,25,38 }, {39,26,38 }, {14,26,39 }, {27,14,39 },
	{29,28,41 }, {42,29,41 }, {30,29,42 }, {43,30,42 }, {30,43,44 },
	{44,31,30 }, {31,44,45 }, {45,32,31 }, {32,45,46 }, {46,33,32 },
	{33,46,47 }, {47,34,33 }, {35,34,47 }, {48,35,47 }, {36,35,48 },
	{49,36,48 }, {37,36,49 }, {50,37,49 }, {38,37,50 }, {51,38,50 },
	{38,51,52 }, {52,39,38 }, {39,52,40 }, {40,27,39 }, {42,41,54 },
	{55,42,54 }, {43,42,55 }, {56,43,55 }, {43,56,57 }, {57,44,43 },
	{44,57,58 }, {58,45,44 }, {45,58,59 }, {59,46,45 }, {46,59,60 },
	{60,47,46 }, {60,61,48 }, {48,47,60 }, {49,48,61 }, {62,49,61 },
	{50,49,62 }, {63,50,62 }, {51,50,63 }, {64,51,63 }, {51,64,65 },
	{65,52,51 }, {52,65,53 }, {53,40,52 }, {55,54,67 }, {68,55,67 },
	{56,55,68 }, {69,56,68 }, {56,69,70 }, {70,57,56 }, {57,70,71 },
	{71,58,57 }, {58,71,72 }, {72,59,58 }, {59,72,73 }, {73,60,59 },
	{61,60,73 }, {74,61,73 }, {62,61,74 }, {75,62,74 }, {63,62,75 },
	{76,63,75 }, {64,63,76 }, {77,64,76 }, {64,77,78 }, {78,65,64 },
	{65,78,66 }, {66,53,65 }, {67,80,81 }, {81,68,67 }, {68,81,82 },
	{82,69,68 }, {70,69,82 }, {83,70,82 }, {71,70,83 }, {84,71,83 },
	{72,71,84 }, {85,72,84 }, {73,72,85 }, {86,73,85 }, {73,86,87 },
	{87,74,73 }, {74,87,88 }, {88,75,74 }, {75,88,89 }, {89,76,75 },
	{76,89,90 }, {90,77,76 }, {78,77,90 }, {91,78,90 }, {66,78,91 },
	{79,66,91 }, {94,81,80 }, {94,80,93 }, {81,94,95 }, {95,82,81 },
	{83,82,95 }, {96,83,95 }, {84,83,96 }, {97,84,96 }, {85,84,97 },
	{98,85,97 }, {86,85,98 }, {99,86,98 }, {86,99,100 }, {100,87,86 },
	{87,100,101 }, {101,88,87 }, {88,101,102 }, {102,89,88 }, {89,102,103 },
	{103,90,89 }, {91,90,103 }, {104,91,103 }, {79,91,104 }, {92,79,104 },
	{93,106,107 }, {107,94,93 }, {94,107,108 }, {108,95,94 }, {96,95,108 },
	{109,96,108 }, {97,96,109 }, {110,97,109 }, {98,97,110 }, {111,98,110 },
	{99,98,111 }, {112,99,111 }, {99,112,113 }, {113,100,99 }, {100,113,114 },
	{114,101,100 }, {101,114,115 }, {115,102,101 }, {102,115,116 },
	{116,103,102 }, {104,103,116 }, {117,104,116 }, {92,104,117 },
	{105,92,117 }, {106,119,120 }, {120,107,106 }, {107,120,121 },
	{121,108,107 }, {109,108,121 }, {122,109,121 }, {110,109,122 },
	{123,110,122 }, {111,110,123 }, {124,111,123 }, {124,125,112 },
	{112,111,124 }, {112,125,126 }, {126,113,112 }, {113,126,127 },
	{127,114,113 }, {114,127,128 }, {128,115,114 }, {115,128,129 },
	{129,116,115 }, {117,116,129 }, {130,117,129 }, {105,117,130 },
	{118,105,130 }
};



	// Init light bulb object

	
	Light_bulb.num_vert = 131;
	Light_bulb.num_tri = 228;
	Light_bulb.num_quad = 0;
	Light_bulb.num_poly = 0;
	Light_bulb.num_surf = 0;

	Light_bulb.vertexList = new VERTEX[Light_bulb.num_vert];
	Light_bulb.triangle = new TRIANGLE[Light_bulb.num_tri];


	for (i=0;i<Light_bulb.num_vert;i++){
		Light_bulb.vertexList[i].coord[0] = vData[i][0];
		Light_bulb.vertexList[i].coord[1] = vData[i][1];
		Light_bulb.vertexList[i].coord[2] = vData[i][2];
	}
	
	for (i=0;i<Light_bulb.num_tri;i++){

			for (k=0;k<3;k++){
				Light_bulb.triangle[i].vertex[k] = &Light_bulb.vertexList[pData[i][k]];
			}
	}

	// Init Arrows object


	Arrows.num_vert = 56;
	Arrows.num_tri = 76;
	Arrows.num_quad = 0;
	Arrows.num_poly = 0;
	Arrows.num_surf = 0;

	Arrows.vertexList = new VERTEX[Arrows.num_vert];
	Arrows.triangle = new TRIANGLE[Arrows.num_tri];

	for (i=0;i<Arrows.num_vert;i++){
		Arrows.vertexList[i].coord[0] = vArrow1[i][0];
		Arrows.vertexList[i].coord[1] = vArrow1[i][1];
		Arrows.vertexList[i].coord[2] = vArrow1[i][2];
	

	}

	for (i=0;i<Arrows.num_tri;i++){

			for (k=0;k<3;k++){
				Arrows.triangle[i].vertex[k] = &Arrows.vertexList[pArrow1[i][k]];
			}
	}

	/* Init Cylinder object*/


	Cyl.num_vert = 27;
	Cyl.num_tri = 36;
	Cyl.num_quad = 0;
	Cyl.num_poly = 0;
	Cyl.num_surf = 0;


	Cyl.vertexList = new VERTEX[Cyl.num_vert];
	Cyl.triangle = new TRIANGLE[Cyl.num_tri];


	for (i=0;i<Cyl.num_vert;i++){
		Cyl.vertexList[i].coord[0] = vCyl[i][0];
		Cyl.vertexList[i].coord[1] = vCyl[i][1];
		Cyl.vertexList[i].coord[2] = vCyl[i][2];
	

	}

	for (i=0;i<Cyl.num_tri;i++){

			for (k=0;k<3;k++){
				Cyl.triangle[i].vertex[k] = &Cyl.vertexList[pCyl[i][k]];
			}
	}


	// Calculate normals

	compute_normals(&Light_bulb);
	compute_normals(&Arrows);
	compute_normals(&Cyl);

//	Rescale_normal(&Light_bulb, 2.5);
//	Rescale_normal(&Arrows, 0.0015);
//	Rescale_normal(&Cyl, 0.0015);


}




void CFiatLuxDoc::free_mem()
{

	delete[] MyModel.surface;
	delete[] MyModel.vertexList;
	delete[] MyModel.triangle;
	delete[] MyModel.quad;
//	delete[] MyModel.poly;
	
}


int CFiatLuxDoc::compute_normals(/*CFiatLuxDoc::*/MODEL *m_Model)
{
	int i,j;
	int nb_adj = 0;


	for (j=0;j<m_Model->num_vert;j++){
	
		m_Model->vertexList[j].normal[0] =0;
		m_Model->vertexList[j].normal[1] =0;
		m_Model->vertexList[j].normal[2] =0;
	}


	//	printf("compute_polys_normals: Triangles\n");
	// Calculate polygons normals

		for (i=0;i<m_Model->num_tri;i++){

			compute_polys_normals(m_Model->triangle[i].vertex[0]->coord, m_Model->triangle[i].vertex[1]->coord, m_Model->triangle[i].vertex[2]->coord, m_Model->triangle[i].normal);
	
		}	
	
//		printf("compute_polys_normals: Quads\n");	
		for (i=0;i<m_Model->num_quad;i++){
		
			compute_polys_normals(m_Model->quad[i].vertex[0]->coord, m_Model->quad[i].vertex[1]->coord, m_Model->quad[i].vertex[2]->coord, m_Model->quad[i].normal);
		}	
	
/*		printf("compute_polys_normals: polys\n");	
		for (i=0;i<MyModel.num_poly;i++){
		
			if (MyModel.poly[i].num_pVertex > 3) compute_polys_normals(MyModel.poly[i].vertex[0]->coord, MyModel.poly[i].vertex[1]->coord, MyModel.poly[i].vertex[2]->coord, MyModel.poly[i].normal);
	
		}	
*/
	

//		printf("compute_vertex_normals\n");
		// Sum up the polys normal for all shared vertices
	
		for (j=0;j<m_Model->num_quad;j++){
									
			for (int l=0;l<4;l++){

				m_Model->quad[j].vertex[l]->normal[0] += m_Model->quad[j].normal[0];
				if (m_Model->quad[j].vertex[l]->normal[0] == 0)
					m_Model->quad[j].vertex[l]->normal[0] = m_Model->quad[j].normal[0];

				m_Model->quad[j].vertex[l]->normal[1] += m_Model->quad[j].normal[1];
				if (m_Model->quad[j].vertex[l]->normal[1] == 0)
					m_Model->quad[j].vertex[l]->normal[1] = m_Model->quad[j].normal[1];
				
				m_Model->quad[j].vertex[l]->normal[2] += m_Model->quad[j].normal[2];
				if (m_Model->quad[j].vertex[l]->normal[2] == 0)
					m_Model->quad[j].vertex[l]->normal[2] = m_Model->quad[j].normal[2];

			}
		}

		for (j=0;j<m_Model->num_tri;j++){
				
			for (int l=0;l<3;l++){


				m_Model->triangle[j].vertex[l]->normal[0] += m_Model->triangle[j].normal[0];
				if (m_Model->triangle[j].vertex[l]->normal[0] == 0)
					m_Model->triangle[j].vertex[l]->normal[0] = m_Model->triangle[j].normal[0];

				m_Model->triangle[j].vertex[l]->normal[1] += m_Model->triangle[j].normal[1];
				if (m_Model->triangle[j].vertex[l]->normal[1] == 0)
					m_Model->triangle[j].vertex[l]->normal[1] = m_Model->triangle[j].normal[1];

				m_Model->triangle[j].vertex[l]->normal[2] += m_Model->triangle[j].normal[2];
				if (m_Model->triangle[j].vertex[l]->normal[2] == 0)
					m_Model->triangle[j].vertex[l]->normal[2] = m_Model->triangle[j].normal[2];
			
			}
		}	
		
	

	//normalize the vertex normal
		for (j=0;j<m_Model->num_vert;j++)
		{
	
			normalise(m_Model->vertexList[j].normal);

		}
	


	 
	
	//
	


	return(1);
}

void CFiatLuxDoc::normalise(float norm[3])
{

	float d = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);
	norm[0] /= d;
	norm[1] /= d;
	norm[2] /= d;

}

void CFiatLuxDoc::Rescale_normal(MODEL *m_Model, GLdouble factor)
{

	int j;


		for (j=0;j<m_Model->num_vert;j++){
			m_Model->vertexList[j].normal[0] *= (float)factor;
			m_Model->vertexList[j].normal[1] *= (float)factor;
			m_Model->vertexList[j].normal[2] *= (float)factor;
		}
	

		for (j=0;j<m_Model->num_tri;j++){
			m_Model->triangle[j].normal[0] *= (float)factor;
			m_Model->triangle[j].normal[1] *= (float)factor;
			m_Model->triangle[j].normal[2] *= (float)factor;
		}

		for (j=0;j<m_Model->num_quad;j++){
	
			m_Model->quad[j].normal[0] *= (float)factor;
			m_Model->quad[j].normal[1] *= (float)factor;
			m_Model->quad[j].normal[2] *= (float)factor;
		}

	/*	for (j=0;j<m_Model->num_poly;j++){
	
			m_Model->poly[j].normal[0] *= (float)factor;
			m_Model->poly[j].normal[1] *= (float)factor;
			m_Model->poly[j].normal[2] *= (float)factor;
		}*/
	


}



void CFiatLuxDoc::compute_polys_normals(float v1[3], float v2[3], float v3[3], float norm[3])
{
	int i;
	float d1[3], d2[3];

	for (i=0;i<3;i++)
	{
		d1[i] = v1[i] - v2[i];
		d2[i] = v2[i] - v3[i];
	}
	
	// cross product of 2 vectors
	norm[0] = d1[1]*d2[2] - d1[2]*d2[1];
	norm[1] = d1[2]*d2[0] - d1[0]*d2[2];
	norm[2] = d1[0]*d2[1] - d1[1]*d2[0];

	// normalize the resulting vector
	
	normalise(norm);



}



/////////////////////////////////////////////////////////////////////////////
// CFiatLuxDoc diagnostics

#ifdef _DEBUG
void CFiatLuxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFiatLuxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxDoc commands









void CFiatLuxDoc::RenderScene(void)
{
//	int i,j;

	// Clear frame buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float v[3];

 //  if (abs(m_xRotate) > 180) m_yRotate *= -1;
 glPushMatrix();
//	
   
		// viewing transformations
		glTranslated(0.0,0.0, -3);
		glScaled(m_Zoom,m_Zoom,-m_Zoom);


	//	PointToVector(m_xRotate, m_yRotate, 800, 800, v);

		printf("m_xRotate: %f  m_yRotate: %f\n", m_xRotate, m_yRotate);

	/*	if (abs(m_xRotate) > 180){
			//m_yRotate *= -1;
			glRotated(-m_yRotate, 0.0, 1.0, 0.0);
		}
		else
		{
			glRotated(m_yRotate, 0.0, 1.0, 0.0);
		}*/

		glRotated(m_xRotate, 1.0, 0.0, 0.0);
		glRotated(m_yRotate, 0.0, 1.0, 0.0);
/*		glRotated(v[0]*30, 1.0, 0.0, 0.0);
		glRotated(-v[1]*30, 0.0, 1.0, 0.0);
		glRotated(v[2]*30, 0.0, 0.0, 1.0);*/
  

//	tessellatePolys();	
		
		if (TR_flag) {
		// Call display list
			glCallList(Disp_list);
	
		//	if (Show_Normal_flag) glCallList(List_Normal);
		}
		else {

	
			switch (Lighting_flag) {
							
			case 1: //Smooth shading diplay
			
				DrawSmoothObject();
			
				break;
		
			case 2: // Flat shading diplay

				DrawFlatObject();
			//	DrawPointObject();
			//	DrawLineStripObject();
			
			} 

			// Display vertex normals

			
		}
		if (Show_Normal_flag) {
				
			DrawVertexNormals();
				
		}

	glPopMatrix();

	if (Move_Light_flag){
		
		//	Display light bulb object to show the position of the light source
		DrawLightBulb();

		// Set light position
		
		float Light_position[]  = { m_xlight_trans, m_ylight_trans, 5.0f, 0.0f};
		float pos[] = { -m_xlight_trans, -m_ylight_trans,0.0f,0.0f};

	
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_POSITION, Light_position);
		
	

		
	}

	
//	Calculate and display FPS
	if (ShowFPS) CalcFPSDeltaT();

 
}


BOOL CFiatLuxDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// OpenGL init
	glEnable(GL_LIGHT0);

	

    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glCullFace(GL_BACK);
	glEnable(GL_NORMALIZE);

	if (FacesCulling) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);



	
	/////////////////////////////////////////////////////////////////


	if (TwoLights){
		glEnable(GL_LIGHT2);
		m_xlight_trans = -2;
		m_ylight_trans = 2;
	}
	else{
		glDisable(GL_LIGHT2);
		m_xlight_trans = 0;
		m_ylight_trans = 0;
	}


	float Light_color2[] = { 0.5,0.5, 0.5 };
	float dir[] = {1,1,0};
	float pos2[] = {2.0,-2.0f,0.0f,0.0f};

	float pos3[] = {m_xlight_trans,m_ylight_trans,5.0f,0.0f};


	glLightfv(GL_LIGHT2, GL_POSITION , pos2);
	glLightfv(GL_LIGHT0, GL_POSITION , pos3);




	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION , dir);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Light_color2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Light_color2);
	////////////////////////////////////////////////////////////////////
	
	
	UpdateColours();	

/*	m_Zoom = 1.0;
	scale = 0.07 ;
	m_ZoomNorm = 1.0;*/

	m_xRotate = 0;
	m_yRotate = 0;

//	Init_flag = 0x0FFF;

	BOOL bDoingBackgroundProcessing = TRUE;

	m_DocPath = lpszPathName;

/*////////////// TEST ////////////////////////////////////////////////
	while ( bDoingBackgroundProcessing ) { 
		MSG msg;
		while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 

    
		{ 
        
			if ( !PumpMessage( ) ) 
        
			{ 
         
				bDoingBackgroundProcessing = FALSE; 
          
				::PostQuitMessage( ); 
           
				break; 
        
			} 
    
		} 
    
		// let MFC do its idle processing
    
		LONG lIdle = 0;
    
		while ( AfxGetApp()->OnIdle(lIdle++ ) )
        ;  
    
		// Perform some background processing here 
   
		// using another call to OnIdle

	}

/////////// END TEST ////////////////////////////////////////////*/



	//UpdateAllViews(NULL);
	return TRUE;
}



void CFiatLuxDoc::OnUpdateTbSolid(CCmdUI* pCmdUI) 
{
	if (Init_flag & 0x000F)
	{
		Init_flag = Init_flag & 0xFFF0;
		pCmdUI->SetCheck(0);
	}
}

void CFiatLuxDoc::OnUpdateTBSmooth(CCmdUI* pCmdUI) 
{
	if (Init_flag & 0x0F00)
	{
		Init_flag = Init_flag & 0xF0FF;
		pCmdUI->SetCheck(1);
	}
}

void CFiatLuxDoc::OnUpdateTBFlat(CCmdUI* pCmdUI) 
{
	if (Init_flag & 0x00F0)
	{
		Init_flag = Init_flag & 0xFF0F;
		pCmdUI->SetCheck(0);
	}
	
}

void CFiatLuxDoc::UpdateColours()
{


	if (!SingleColor) glEnable(GL_COLOR_MATERIAL );
	else
	{
		glDisable(GL_COLOR_MATERIAL );
	}
	

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT );
	glColor3fv(mat_ambient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR );
	glColor3fv(mat_specular);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE );

	// Set material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

 	

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	
	// Set light colour
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_color);
	

	float Light_color2[] = {1.0,1.0,1.0};

	glLightfv(GL_LIGHT1, GL_SPECULAR, Light_color2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_color2);
	

	// Set backgroung colour
    glClearColor(bkg_color[0], bkg_color[1], bkg_color[2], 0.0);

	

}


void CFiatLuxDoc::CalcFPSDeltaT(){


	static int timeinit=0;
	static int start,start2,current,last;
	static int frame=0, frame2=0;

	if(!timeinit){
		frame=0;
		start=timeGetTime();
		timeinit=1;
	}
	frame++;
	frame2++;
	current=timeGetTime(); // found in winmm.lib
	double dif=(double)(current-start)/CLOCKS_PER_SEC;
	double rv = (dif)? (double)frame/(double)dif:-1.0;
	if(dif>2.0 && frame >10) {
		start  = start2;
		frame  = frame2;
		start2 = timeGetTime();
		frame2 = 0;
	}		   
	DeltaT = (float)(current-last)/CLOCKS_PER_SEC;
	if(current==last) { 
		DeltaT = 0.1f / CLOCKS_PER_SEC;  // it just cant be 0
	}
	// if(DeltaT>1.0) DeltaT=1.0;
	FPS = (float)rv;
	last = current;


	CString fps_str;
	char str[20];
		
	fps_str = "FPS: " + (CString)gcvt(FPS,4,str);
//	fps_str = "Zoom: " + (CString)gcvt(m_Zoom,4,str);
	
	CWnd* MyCWnd = AfxGetMainWnd( );

	MyCWnd->SetWindowText(fps_str);


	
}



void CFiatLuxDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
//	free_mem();
	CDocument::OnCloseDocument();
}

int CFiatLuxDoc::Save_to_txt()
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260]="FiatLuxDebug.log";       // buffer for filename
	HWND hwnd;              // owner window
	HANDLE hf;              // file handle
	int i;



	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Debug log (*.log)\0*.log\0All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	// Display the Open dialog box. 

	if (GetSaveFileName(&ofn)==TRUE) 
	{

		ofstream ostr(ofn.lpstrFile);

		ostr << "// Number of vertices"<< endl;
		ostr << "int nbVertices = "<< MyModel.num_vert << ";"<< endl;
		ostr << "// Number of triangles"<< endl;
		ostr << "int nbTriangles = "<< MyModel.num_tri << ";"<< endl;
		ostr << "// Number of quads"<< endl;
		ostr << "int nbQuads = "<< MyModel.num_quad << ";"<< endl;
		ostr << endl;

		ostr << "// Start vertices data"<< endl;
		ostr << "float vData[][3] = {"<< endl;

		for (i=0;i<MyModel.num_vert;i++){
				
				
			ostr << "	{" 
				 << MyModel.vertexList[i].coord[0] << "f, " 
				 << MyModel.vertexList[i].coord[1] << "f, " 
				 << MyModel.vertexList[i].coord[2] << "f},"
				 << endl;
		}

		ostr << "};"<< endl;
		ostr << "// End vertices data"<< endl;
		ostr << endl;


		ostr << "// Start triangles data"<< endl;
		ostr << "float tData[][3] = {"<< endl;

		for (i=0;i<MyModel.num_tri;i++){
				
		
			ostr << MyModel.triangle[i].surf_Ref <<" ";
		}

		ostr << "};"<< endl;
		ostr << "// End triangles data"<< endl;
		ostr << endl;

	/*	ostr << "// Start quads data"<< endl;
		ostr << "float qData[][3] = {"<< endl;

		for (i=0;i<MyModel.num_poly;i++){
		//	if 	(MyModel.poly[i].num_pVertex > 2048){
				ostr <<	MyModel.poly[i].num_pVertex << 
					MyModel.surface[MyModel.poly[i].surf_Ref].name
					<<endl;
		//	}
				
		ostr << "[" 
				 << MyModel.poly[i].normal[0] << "][" 
				 << MyModel.poly[i].normal[1] << "][" 
				 << MyModel.poly[i].normal[2] << "]"
				 << endl;
		}

		ostr << "};"<< endl;
		ostr << "// End quads data"<< endl;*/
	
		ostr.close();
		 
	}
	
	
	return 0;
   

}

void CFiatLuxDoc::DrawLightBulb()
{

		#define Val 3.0

		static float posL0[] = { -Val, Val, 5.0f, 0.0f};
		static float posL2[] = { Val, -Val, 0.0f, 0.0f};
		int i;
		
	
/*
		glPushMatrix();	
		// Set light position
		
		GLfloat Light_position[]  = { -2, 2, 5.0f, 0.0f};
		float pos[] = { 2, -2,0.0f,0.0f};

		glRotated(-m_ylight_trans*5, 1.0, 0.0, 0.0);
		glRotated(m_xlight_trans*5, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_POSITION, Light_position);
		
	
  
		
		glPopMatrix();
*/

		
		glPushAttrib(GL_ENABLE_BIT|GL_POLYGON_BIT);
	
		glEnable(GL_LIGHTING);
	//	glDisable(GL_LIGHT0);
	//	glDisable(GL_LIGHT2);
	//	glEnable(GL_LIGHT1);
		glDisable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);	
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		glPushMatrix();
		
		glLightfv(GL_LIGHT2, GL_POSITION, posL2);
		glLightfv(GL_LIGHT0, GL_POSITION, posL0);

		glTranslated(0.0,0.0, -3);
	//	glScaled(2.5,2.5,2.5);
		glTranslated(m_xlight_trans/10,m_ylight_trans/10,0.0);

		
		

	//	glRotated(90.0, 1.0, 0.0, 0.0);
	//	glRotated(180.0, 0.0, 1.0, 0.0);
	//	glRotated(180.0, 0.0, 0.0, 1.0);
		
	//	glDisable(GL_LIGHTING);
	
		
		glBegin(GL_TRIANGLES);
	
	

	//	glColor3fv(Light_color);
		glColor3f(1.0,1.0,0.0);

			for (i=0;i<Light_bulb.num_tri;i++){
		
				glNormal3fv(Light_bulb.triangle[i].vertex[0]->normal);
				glVertex3fv(Light_bulb.triangle[i].vertex[0]->coord);
				glNormal3fv(Light_bulb.triangle[i].vertex[1]->normal);
				glVertex3fv(Light_bulb.triangle[i].vertex[1]->coord);
				glNormal3fv(Light_bulb.triangle[i].vertex[2]->normal);
				glVertex3fv(Light_bulb.triangle[i].vertex[2]->coord);
			}
		
		glColor3f(0.5,0.5,0.5);

			for (i=0;i<Cyl.num_tri;i++){
		
				glNormal3fv(Cyl.triangle[i].vertex[0]->normal);
				glVertex3fv(Cyl.triangle[i].vertex[0]->coord);
				glNormal3fv(Cyl.triangle[i].vertex[1]->normal);
				glVertex3fv(Cyl.triangle[i].vertex[1]->coord);
				glNormal3fv(Cyl.triangle[i].vertex[2]->normal);
				glVertex3fv(Cyl.triangle[i].vertex[2]->coord);
			}

		glEnd();

	//	glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
	  
		glColor3f(1.0,0.0,0.0);

		for (i=0;i<Arrows.num_tri;i++){
					
			glNormal3fv(Arrows.triangle[i].normal);

			glVertex3fv(Arrows.triangle[i].vertex[0]->coord);
		//	glNormal3fv(Arrows.triangle[i].vertex[1]->normal);
			glVertex3fv(Arrows.triangle[i].vertex[1]->coord);
		//	glNormal3fv(Arrows.triangle[i].vertex[2]->normal);
			glVertex3fv(Arrows.triangle[i].vertex[2]->coord);
		}

	
		glEnd();

		glPopMatrix();

		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT2);
	
		glPopAttrib();

}

void CFiatLuxDoc::DrawSmoothObject()
{
	int i;

	glBegin(GL_TRIANGLES);

	for (i=0;i<MyModel.num_tri;i++){
	
		glColor3fv(MyModel.surface[(MyModel.triangle[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.triangle[i].vertex[0]->normal);
		glVertex3fv(MyModel.triangle[i].vertex[0]->coord);
		glNormal3fv(MyModel.triangle[i].vertex[1]->normal);
		glVertex3fv(MyModel.triangle[i].vertex[1]->coord);
		glNormal3fv(MyModel.triangle[i].vertex[2]->normal);
		glVertex3fv(MyModel.triangle[i].vertex[2]->coord);
	}	

	glEnd();

	glBegin(GL_QUADS);
	
	for (i=0;i<MyModel.num_quad;i++){
		
		glColor3fv(MyModel.surface[(MyModel.quad[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.quad[i].vertex[0]->normal);
		glVertex3fv(MyModel.quad[i].vertex[0]->coord);
		glNormal3fv(MyModel.quad[i].vertex[1]->normal);
		glVertex3fv(MyModel.quad[i].vertex[1]->coord);
		glNormal3fv(MyModel.quad[i].vertex[2]->normal);
		glVertex3fv(MyModel.quad[i].vertex[2]->coord);
		glNormal3fv(MyModel.quad[i].vertex[3]->normal);
		glVertex3fv(MyModel.quad[i].vertex[3]->coord);
		
	}	

	glEnd();


	

}

void CFiatLuxDoc::DrawFlatObject()
{

	int i;

	glBegin(GL_TRIANGLES);
	for (i=0;i<MyModel.num_tri;i++){
	
		glColor3fv(MyModel.surface[(MyModel.triangle[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.triangle[i].normal);
		glVertex3fv(MyModel.triangle[i].vertex[0]->coord);
		glVertex3fv(MyModel.triangle[i].vertex[1]->coord);
		glVertex3fv(MyModel.triangle[i].vertex[2]->coord);		
		
	}	
	glEnd();

	glBegin(GL_QUADS);
		
	for (i=0;i<MyModel.num_quad;i++){
		
		glColor3fv(MyModel.surface[(MyModel.quad[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.quad[i].normal);
		glVertex3fv(MyModel.quad[i].vertex[0]->coord);
		glVertex3fv(MyModel.quad[i].vertex[1]->coord);
		glVertex3fv(MyModel.quad[i].vertex[2]->coord);
		glVertex3fv(MyModel.quad[i].vertex[3]->coord);
				
	}
	glEnd();


}

void CFiatLuxDoc::DrawVertexNormals()
{
	int i;

	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_LINES);
	
	for (i=0;i<MyModel.num_vert;i++){
		
		glNormal3fv(MyModel.vertexList[i].normal);
		glVertex3fv(MyModel.vertexList[i].coord);
		glVertex3f(MyModel.vertexList[i].coord[0] + scale * ((MyModel.vertexList[i].normal[0]) / (float)m_ZoomNorm),
				   MyModel.vertexList[i].coord[1] + scale * ((MyModel.vertexList[i].normal[1]) / (float)m_ZoomNorm),
				   MyModel.vertexList[i].coord[2] + scale * ((MyModel.vertexList[i].normal[2]) / (float)m_ZoomNorm));
				
	}
		
	glEnd();


}


void CFiatLuxDoc::DrawPointObject()
{

	int i;

/*	glPointSize(5.0f);

	glEnable(GL_POINT_SMOOTH);
 */

	glColor3f(0.9f,0.9f,0.9f);
	
	glBegin(GL_POINTS);

	for (i=0;i<MyModel.num_vert;i++){
	
		
		glNormal3fv(MyModel.vertexList[i].normal);
		glVertex3fv(MyModel.vertexList[i].coord);
	
	}	

	
	glEnd();

}


void CFiatLuxDoc::DrawLineStripObject()
{

	int i;

	glBegin(GL_LINE_LOOP );
	for (i=0;i<MyModel.num_tri;i++){
	
		glColor3fv(MyModel.surface[(MyModel.triangle[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.triangle[i].normal);
		glVertex3fv(MyModel.triangle[i].vertex[0]->coord);
		glVertex3fv(MyModel.triangle[i].vertex[1]->coord);
		glVertex3fv(MyModel.triangle[i].vertex[2]->coord);		
		
	}	

	for (i=0;i<MyModel.num_quad;i++){
		
		glColor3fv(MyModel.surface[(MyModel.quad[i].surf_Ref)].colorRGBA);
		glNormal3fv(MyModel.quad[i].normal);
		glVertex3fv(MyModel.quad[i].vertex[0]->coord);
		glVertex3fv(MyModel.quad[i].vertex[1]->coord);
		glVertex3fv(MyModel.quad[i].vertex[2]->coord);
		glVertex3fv(MyModel.quad[i].vertex[3]->coord);
	}

	glEnd();




}


void CFiatLuxDoc::tessellatePolys()
{



	//	Tesselate non convex polys
	GLUtesselator* tobj;
	int i,k,j;
	double rect[MAXPOINT][3];
	

	

	

	tobj = gluNewTess();
	
	//gluTessCallback(tobj, GLU_TESS_VERTEX, (GLvoid(CALLBACK *)()) &glVertex3dv); 
	gluTessCallback(tobj, GLU_TESS_VERTEX_DATA, (GLvoid(CALLBACK *)()) &vertexDataCallBack); 
//   	gluTessCallback(tobj, GLU_TESS_BEGIN_DATA, (GLvoid(CALLBACK *)()) &beginDataCallback);
//	gluTessCallback(tobj, GLU_TESS_END_DATA, (GLvoid(CALLBACK *)()) &endDataCallback);  
	gluTessCallback(tobj, GLU_TESS_EDGE_FLAG, (GLvoid(CALLBACK *)()) &glEdgeFlag);  

	MyModel.current_tri = MyModel.num_tri;
	MyModel.current_vtx = 0;


		
	for (i=0;i<MyModel.num_poly;i++){

		MyModel.current_poly = i;

		gluTessBeginPolygon(tobj, &MyModel);
			

			gluTessBeginContour(tobj);

			for (k=0;k<3;k++){
				for (j=0;j<MyModel.poly[i].num_pVertex;j++){
					rect[j][k] = (double)MyModel.poly[i].vertex[j]->coord[k];
				}
			}

			for (j=0;j<MyModel.poly[i].num_pVertex;j++){

				
		
				gluTessVertex(tobj,rect[j], rect[j]);
			}

			gluTessEndContour(tobj);

		gluTessEndPolygon(tobj); 

		

	}

			
	gluDeleteTess(tobj);
	delete[] MyModel.poly;


}




void CALLBACK CFiatLuxDoc::vertexCallBack(void *vertex)
{

}

void CALLBACK CFiatLuxDoc::vertexDataCallBack(void *vertex_data, void *model_data)
{

	double *vCoord;
	float test[3];
	MODEL *tModel;

	tModel = (MODEL *)model_data;

	vCoord = (double*)vertex_data;
	test[0] = (float)vCoord[0];
	test[1] = (float)vCoord[1];
	test[2] = (float)vCoord[2];


	for (int j=0;j<tModel->poly[tModel->current_poly].num_pVertex;j++){
		
		if (compareVtx(test, tModel->poly[tModel->current_poly].vertex[j]->coord)){

			tModel->triangle[tModel->current_tri].vertex[tModel->current_vtx] = tModel->poly[tModel->current_poly].vertex[j];
			tModel->triangle[tModel->current_tri].surf_Ref = tModel->poly[tModel->current_poly].surf_Ref;
		}
	
	}

	tModel = (MODEL *)model_data;
	
	if (++tModel->current_vtx > 2){
		tModel->current_tri++;
		tModel->current_vtx = 0;
	} 


	glVertex3dv(vCoord);


}


void CALLBACK CFiatLuxDoc::beginDataCallback(GLenum type, void *model_data)
{

	MODEL *tModel;

	tModel = (MODEL *)model_data;


	glBegin(type);



}

void CALLBACK CFiatLuxDoc::endDataCallback(void *model_data)
{

	MODEL *tModel;


	glEnd();

	tModel = (MODEL *)model_data;
	
//	tModel->current_tri++;




}

int CFiatLuxDoc::compareVtx(float *v1, float *v2)
{


	if ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2])){
		return 1;
	}
	else{
		return 0;
	}
	
}




void CFiatLuxDoc::PointToVector(int x, int y, int width, int height, float v[])
{

 float d, a;

  /* project x, y onto a hemi-sphere centered within width, height. */
  v[0] = (2.0 * x - width) / width;
  v[1] = (height - 2.0 * y) / height;
  d = sqrt(v[0] * v[0] + v[1] * v[1]);
  v[2] = cos((3.14159265 / 2.0) * ((d < 1.0) ? d : 1.0));
  
  
  
  a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;

  printf("v0: %f v1: %f v2: %f d: %f\n", v[0], v[1], v[2], d);


}
