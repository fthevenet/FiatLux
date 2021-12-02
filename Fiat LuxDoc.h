// Fiat LuxDoc.h : interface of the CFiatLuxDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIATLUXDOC_H__6C41F9CA_C5AA_11D2_B626_002018549ABD__INCLUDED_)
#define AFX_FIATLUXDOC_H__6C41F9CA_C5AA_11D2_B626_002018549ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Progess.h"



#ifndef CALLBACK 
#define CALLBACK



#endif

#define MAXPOINT 4048

class CFiatLuxDoc : public CDocument
{
protected: // create from serialization only
	CFiatLuxDoc();
	DECLARE_DYNCREATE(CFiatLuxDoc)

// Attributes
public:

	GLdouble m_yRotate;
	GLdouble m_xRotate;
	GLdouble m_Zoom;
	GLdouble m_ZoomNorm;
	GLdouble m_ylight_trans;
	GLdouble m_xlight_trans;
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat bkg_color[3];
	GLfloat Light_color[4];
	GLfloat mat_shininess;
	
	CString m_DocPath;
//	int nb_surf;
//	int List_flat;		// display list indexes
//	int List_smooth;
//	int List_Normal;
	int Disp_list;
//	int Tess_list;
//	int nv; // number of vertices
//	int nt; // number of triangles
//	int nq; // number of quads
//	int np; // number of polys with more than 4 vertices
//	int nt_supp;  // number of triangularised polygons
//	int timeinit;
	void disp_infos();
	float center[3], max[3], min[3];
	float maxsize;
	float scale;
	float DeltaT, FPS;
	BOOL TR_flag;
	BOOL SingleColor;
	BOOL Show_Normal_flag;
	BOOL ShowFPS;
	BOOL FacesCulling;
	BOOL TwoLights;
	int Lighting_flag;
	int Move_Light_flag;


	typedef struct tagSURFACE              
	{
		CString  name;              
		float colorRGBA[4];
		
		
	} SURFACE; 
	
//	SURFACE *MySurf[1024];


	typedef struct tagVERTEX
	{
		float coord[3];
		float normal[3];

	//	float u, v;
	} VERTEX;

	typedef struct tagTRIANGLE
	{
		VERTEX *vertex[3];
		float normal[3];
		int surf_Ref;

	} TRIANGLE;
	
	typedef struct tagQUAD
	{
		VERTEX *vertex[4];
		float normal[3];
		int surf_Ref;

	} QUAD;
	
	typedef struct tagPOLY
	{
		VERTEX *vertex[MAXPOINT];
		int num_pVertex;
		float normal[3];
		int surf_Ref;

	} POLY;

	typedef struct tagMODEL
	{
	
		int num_tri;
		int num_quad;
		int num_poly;
		int num_surf;
		int num_vert;
		int num_tess_tri;
		int current_tri;
		int current_vtx;
		int current_poly;
	
		TRIANGLE* triangle;
		QUAD *quad;
		POLY *poly;
		SURFACE *surface;
		VERTEX *vertexList;

	} MODEL;

	MODEL MyModel, Light_bulb, Arrows, Cyl;			


	void Rescale_normal(MODEL *m_Model, GLdouble factor);


//	char* m_pVal;
	
	void RenderScene(void);
	void UpdateColours();
	void CalcFPSDeltaT();
	int build_disp_list();
	void Dump_disp_list();



public:
//	char* GetByte() { return m_pVal; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiatLuxDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLineStripObject();
	void DrawPointObject();
	static int compareVtx(float *v1, float *v2);
	static void CALLBACK endDataCallback(void *model_data);
	static void CALLBACK beginDataCallback(GLenum type, void *model_data);
	static void CALLBACK vertexDataCallBack(void *vertex_data, void *model_data);
	static void CALLBACK vertexCallBack(void *vertex);
	void tessellatePolys();
	void DrawVertexNormals();
	void DrawFlatObject();
	void DrawSmoothObject();
	void DrawLightBulb();
	int Save_to_txt();
	virtual ~CFiatLuxDoc(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Helpers for reading LWO files
	char* get_ID4(CFile* fp);
	CString get_S0(CFile* fp);
	unsigned short int get_U2(CFile* fp);
	unsigned char get_U1(CFile* fp);
	unsigned short int mem_get_U2(char* buf, int i);

	short int get_I2(CFile* fp);
	short int mem_get_I2(char* buf, int i);

	int get_I4(CFile* fp);
	int mem_get_I4(char* buf, int i);

	unsigned int get_U4(CFile* fp);
	unsigned int mem_get_U4(char* buf, int i);

	float get_F4(CFile* fp);
	float mem_get_F4(char* buf, int i);

	int find_chunk(CFile* fp, char * chunk, BOOL FromStart );
	int read_LWOB(CFile* fp);
//	int IsConcave(float* v1, float* v2, float* v3);
	void free_mem(void);
	void Init_Light_Obj();

	unsigned short int Init_flag;

	CProgess* m_pModeless;



	//object data
	
//	float* vertices; // array defining vertices
//	unsigned short int* triangles;	// array defining triangles
//	unsigned short int* quads;		// array defining quads
//	unsigned short int* polys;		// array defining non-standards polys
//	float* tri_normals;
//	float* quad_normals;
//	float* vertex_normals;
//	int* nb_adj_poly;

	
	int compute_normals(MODEL *m_Model);
	void compute_polys_normals(float v1[3], float v2[3], float v3[3], float norm[3]);
	void normalise(float norm[3]);




// Generated message map functions
protected:
	void PointToVector(int x, int y, int width, int height, float v[3]);
	//{{AFX_MSG(CFiatLuxDoc)
	afx_msg void OnUpdateTbSolid(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTBSmooth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTBFlat(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIATLUXDOC_H__6C41F9CA_C5AA_11D2_B626_002018549ABD__INCLUDED_)
