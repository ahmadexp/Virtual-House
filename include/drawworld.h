void TestApp::drawworld(){

	if (!start_motion) {
		printf("DEBUG: drawworld.h - drawworld() start\n");
		fflush(stdout);
	}
	if(usetextures)glEnable(GL_TEXTURE_2D);								
	if(usetextures)glBindTexture(GL_TEXTURE_2D,wireframetexture);		
	glEnableClientState(GL_VERTEX_ARRAY);
	if(usetextures)glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if(usetextures)
		skybox->Render(camyang*degreesinradian,camxang*degreesinradian);
	else
	glClearColor(0, 0.16, 0.35, 1);      // bakgournd sky color

	//draw world
	gameworldpolygons=0;
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
		for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
			for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++){
				int a=worldgrid[x][y][z][0];
				int b=worldgrid[x][y][z][1];
				if(a>0 && worldtileinterleavedvertex[a][b] != NULL){
					if(usetextures){										
						glEnable(GL_TEXTURE_2D);
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindTexture(GL_TEXTURE_2D,worldtiletexture[a]);
							
					}																		
					glPushMatrix();
					glTranslatef(x*worldtilesize,y*worldtilesize,z*worldtilesize);
					glVertexPointer(3,GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->px);
					if(usetextures||a==10||a>=45)glTexCoordPointer(2,GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->tx);
					glNormalPointer(GL_FLOAT,sizeof(InterleavedVertex),&worldtileinterleavedvertex[a][b]->nx);
					glDrawArrays(GL_TRIANGLES,0,worldtilevertexcount[a]);
					if(!usetextures){glDisable(GL_TEXTURE_2D);glDisableClientState(GL_TEXTURE_COORD_ARRAY);}    //added
					glPopMatrix();			
					gameworldpolygons+=worldtilevertexcount[a]/3;
				}
			}


	if(usetextures)glBindTexture(GL_TEXTURE_2D,wireframetexture);

	//draw player
	if(showplayer && playervertexarray != NULL){
		playerms3dmodel.SetFrame(playerframe);
		int vertnum=0;
		int numGroups = playerms3dmodel.GetNumGroups();
		for (int i = 0; i < numGroups; i++){
			ms3d_group_t *group = playerms3dmodel.GetGroup(i);
			for (size_t j = 0; j < group->triangleIndices.size(); j++){
				ms3d_triangle_t *triangle = playerms3dmodel.GetTriangle(group->triangleIndices[j]);
				for (int v = 0; v < 3; v++){
					ms3d_vertex_t *playervertex = playerms3dmodel.GetVertex(triangle->vertexIndices[v]);
					float pos[3];
					playerms3dmodel.TransformVertex(playervertex,pos);
					playervertexarray[vertnum*3+0]=pos[0]*0.05;
					playervertexarray[vertnum*3+1]=pos[1]*0.05;
					playervertexarray[vertnum*3+2]=pos[2]*0.05;
					vertnum+=1;
				}
			}
		}
		glPushMatrix();
		glTranslatef(playerxpos,playerypos,playerzpos);
		glRotatef(-playeryang*degreesinradian+90,0,1,0);
		glVertexPointer(3,GL_FLOAT,0,playervertexarray);
		if(usetextures)glTexCoordPointer(2,GL_FLOAT,0,playertexturearray);
		glNormalPointer(GL_FLOAT,0,playernormalarray);
		glDrawArrays(GL_TRIANGLES,0,playervertexcount);
		glPopMatrix();
	}


	//draw entities
	for(int x=highint(0,playerxgridpos-worldtileviewrange); x<lowint(worldgridsizex,playerxgridpos+worldtileviewrange+1); x++)
	for(int y=highint(0,playerygridpos-worldtileviewrange); y<lowint(worldgridsizey,playerygridpos+worldtileviewrange+1); y++)
	for(int z=highint(0,playerzgridpos-worldtileviewrange); z<lowint(worldgridsizez,playerzgridpos+worldtileviewrange+1); z++)
	for(int a=0; a<entitycount[x][y][z]; a++){
		glPushMatrix();
		glTranslatef(
			entitylist[x][y][z][a]->xpos,
			entitylist[x][y][z][a]->ypos,
			entitylist[x][y][z][a]->zpos);
		glRotatef(entitylist[x][y][z][a]->xang*degreesinradian,1,0,0);
		glRotatef(entitylist[x][y][z][a]->yang*degreesinradian,0,1,0);
		glRotatef(entitylist[x][y][z][a]->zang*degreesinradian,0,0,1);
		
		int type = entitylist[x][y][z][a]->type;
		if (entityvertexarray[type] != NULL) {
			glVertexPointer(3,GL_FLOAT,0,entityvertexarray[type]);
			if(usetextures)glTexCoordPointer(2,GL_FLOAT,0,entitytexturearray[type]);
			glNormalPointer(GL_FLOAT,0,entitynormalarray[type]);
			glDrawArrays(GL_TRIANGLES,0,entityvertexcount[type]);
		}
		glPopMatrix();
	}

	//finished drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	if(usetextures)glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	if(usetextures)glDisable(GL_TEXTURE_2D);

}
