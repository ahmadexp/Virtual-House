//#include "gamespecific/ms3d/mathlib.cpp"
//#include "gamespecific/ms3d/msModel.cpp"
#include "../gamespecific/ms3d/mathlib.h"
#include "../gamespecific/ms3d/msModel.h"
msModel playerms3dmodel;

void loadms3d(char* filename,
			  msModel& milkshapmodel,
			  float*& vertexarray,
			  float*& texturearray,
			  float*& normalarray,
			  int &outputarraysize,float scale){

	// Initialize output parameters to safe values
	vertexarray = NULL;
	texturearray = NULL;
	normalarray = NULL;
	outputarraysize = 0;
	
	if (!milkshapmodel.Load(filename)) {
		printf("ERROR: loadms3d() - failed to load '%s'\n", filename);
		return;
	}
	
	milkshapmodel.SetupJoints();

	// Calculate total triangles from groups to ensure correct allocation size
	int numGroups = milkshapmodel.GetNumGroups();
	int totalTrianglesInGroups = 0;
	for (int i = 0; i < numGroups; i++) {
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		totalTrianglesInGroups += group->triangleIndices.size();
	}

	// Use the count from groups as that's what we iterate over
	outputarraysize = totalTrianglesInGroups * 3;
	
	// Safety check
	if (outputarraysize == 0) {
		return;
	}

	vertexarray = new float[outputarraysize*3];
	int vertnum=0;
	int numModelVertices = milkshapmodel.GetNumVertices();
	int numModelTriangles = milkshapmodel.GetNumTriangles();

	for (int i = 0; i < numGroups; i++){
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		for (size_t j = 0; j < group->triangleIndices.size(); j++){
			int triIndex = group->triangleIndices[j];
			
			if (triIndex < 0 || triIndex >= numModelTriangles) {
				continue; // Skip invalid triangle
			}
			
			ms3d_triangle_t *triangle = milkshapmodel.GetTriangle(triIndex);
			for (int v = 0; v < 3; v++){
				int vIndex = triangle->vertexIndices[v];
				if (vIndex < 0 || vIndex >= numModelVertices) {
					// initialize with 0 to avoid garbage
					vertexarray[vertnum*3+0]=0;
					vertexarray[vertnum*3+1]=0;
					vertexarray[vertnum*3+2]=0;
				} else {
					ms3d_vertex_t *vertex = milkshapmodel.GetVertex(vIndex);
					vertexarray[vertnum*3+0]=vertex->vertex[0]*0.05;
					vertexarray[vertnum*3+1]=vertex->vertex[1]*0.05;
					vertexarray[vertnum*3+2]=vertex->vertex[2]*0.05;
				}
				vertnum+=1;
			}
		}
	}

	texturearray = new float[outputarraysize*2];
	int trinum=0;
	for (int i = 0; i < numGroups; i++){
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		for (size_t j = 0; j < group->triangleIndices.size(); j++){
			int triIndex = group->triangleIndices[j];
			if (triIndex < 0 || triIndex >= numModelTriangles) continue;

			ms3d_triangle_t *triangle = milkshapmodel.GetTriangle(triIndex);
			texturearray[trinum*3*2+0]=triangle->s[0];
			texturearray[trinum*3*2+1]=triangle->t[0];
			texturearray[trinum*3*2+2]=triangle->s[1];
			texturearray[trinum*3*2+3]=triangle->t[1];
			texturearray[trinum*3*2+4]=triangle->s[2];
			texturearray[trinum*3*2+5]=triangle->t[2];
			trinum+=1;
		}
	}

	normalarray = new float[outputarraysize*3];
	trinum=0;
	for (int i = 0; i < numGroups; i++){
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		for (size_t j = 0; j < group->triangleIndices.size(); j++){
			int triIndex = group->triangleIndices[j];
			if (triIndex < 0 || triIndex >= numModelTriangles) continue;

			ms3d_triangle_t *triangle = milkshapmodel.GetTriangle(triIndex);
			normalarray[trinum*3*3+0]=triangle->vertexNormals[0][0];
			normalarray[trinum*3*3+1]=triangle->vertexNormals[0][1];
			normalarray[trinum*3*3+2]=triangle->vertexNormals[0][2];
			normalarray[trinum*3*3+3]=triangle->vertexNormals[1][0];
			normalarray[trinum*3*3+4]=triangle->vertexNormals[1][1];
			normalarray[trinum*3*3+5]=triangle->vertexNormals[1][2];
			normalarray[trinum*3*3+6]=triangle->vertexNormals[2][0];
			normalarray[trinum*3*3+7]=triangle->vertexNormals[2][1];
			normalarray[trinum*3*3+8]=triangle->vertexNormals[2][2];
			trinum+=1;
		}
	}
}
