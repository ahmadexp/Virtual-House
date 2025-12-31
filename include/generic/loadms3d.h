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

	// CRITICAL FIX: Initialize output parameters to safe values
	vertexarray = NULL;
	texturearray = NULL;
	normalarray = NULL;
	outputarraysize = 0;
	
	printf("DEBUG: loadms3d() - loading '%s'\n", filename);
	fflush(stdout);

	if (!milkshapmodel.Load(filename)) {
		printf("ERROR: loadms3d() - failed to load '%s'\n", filename);
		fflush(stdout);
		return;
	}
	
	printf("DEBUG: loadms3d() - Checkpoint 1: Calling SetupJoints()\n");
	fflush(stdout);
	milkshapmodel.SetupJoints();
	printf("DEBUG: loadms3d() - Checkpoint 2: SetupJoints() returned\n");
	fflush(stdout);

	// Calculate total triangles from groups to ensure correct allocation size
	int numGroups = milkshapmodel.GetNumGroups();
	int totalTrianglesInGroups = 0;
	for (int i = 0; i < numGroups; i++) {
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		totalTrianglesInGroups += group->triangleIndices.size();
	}

	printf("DEBUG: loadms3d() - NumGroups: %d, TotalTrianglesInGroups: %d, GetNumTriangles: %d\n", 
		   numGroups, totalTrianglesInGroups, milkshapmodel.GetNumTriangles());
	fflush(stdout);

	// Use the count from groups as that's what we iterate over
	outputarraysize = totalTrianglesInGroups * 3;
	
	// Safety check
	if (outputarraysize == 0) {
		printf("WARNING: loadms3d() - Model has no triangles in groups\n");
		fflush(stdout);
		return;
	}

	printf("DEBUG: loadms3d() - Allocating vertexarray (size %d floats)\n", outputarraysize * 3);
	fflush(stdout);
	
	vertexarray = new float[outputarraysize*3];
	int vertnum=0;
	int numModelVertices = milkshapmodel.GetNumVertices();
	int numModelTriangles = milkshapmodel.GetNumTriangles();

	for (int i = 0; i < numGroups; i++){
		ms3d_group_t *group = milkshapmodel.GetGroup(i);
		for (size_t j = 0; j < group->triangleIndices.size(); j++){
			int triIndex = group->triangleIndices[j];
			
			if (triIndex < 0 || triIndex >= numModelTriangles) {
				printf("ERROR: loadms3d() - Invalid triangle index %d at group %d index %zu\n", triIndex, i, j);
				fflush(stdout);
				continue; // Skip invalid triangle
			}
			
			ms3d_triangle_t *triangle = milkshapmodel.GetTriangle(triIndex);
			for (int v = 0; v < 3; v++){
				int vIndex = triangle->vertexIndices[v];
				if (vIndex < 0 || vIndex >= numModelVertices) {
					printf("ERROR: loadms3d() - Invalid vertex index %d in triangle %d\n", vIndex, triIndex);
					fflush(stdout);
					// initialize with 0 to avoid garbage
					vertexarray[vertnum*3+0]=0;
					vertexarray[vertnum*3+1]=0;
					vertexarray[vertnum*3+2]=0;
				} else {
					ms3d_vertex_t *vertex = milkshapmodel.GetVertex(vIndex);
					// Note: scale parameter was ignored in original code, using hardcoded 0.05
					// Preserving original behavior but it looks suspicious (maybe should use scale?)
					vertexarray[vertnum*3+0]=vertex->vertex[0]*0.05;
					vertexarray[vertnum*3+1]=vertex->vertex[1]*0.05;
					vertexarray[vertnum*3+2]=vertex->vertex[2]*0.05;
				}
				vertnum+=1;
			}
		}
	}
	
	printf("DEBUG: loadms3d() - Checkpoint 3: Vertex array filled\n");
	fflush(stdout);

	printf("DEBUG: loadms3d() - Allocating texturearray (size %d floats)\n", outputarraysize * 2);
	fflush(stdout);

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

	printf("DEBUG: loadms3d() - Checkpoint 4: Texture array filled\n");
	fflush(stdout);
	
	printf("DEBUG: loadms3d() - Allocating normalarray (size %d floats)\n", outputarraysize * 3);
	fflush(stdout);

	normalarray = new float[outputarraysize*3];
	trinum=0; // fixed shadowed variable or reset it properly
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

	printf("DEBUG: loadms3d() - Checkpoint 5: Normal array filled. Done.\n");
	fflush(stdout);

}
