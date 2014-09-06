/* 
 * File:   BulletConversions.hpp
 * Author: missvaleska
 *
 * Created on September 6, 2014, 12:26 AM
 */

#ifndef BULLETCONVERSIONS_HPP
#define	BULLETCONVERSIONS_HPP

#include "OpenHorizonsIncludes.hpp"

btTriangleMesh* ConvertIrrMeshToBulletTriangleMesh(scene::IMesh* pMesh,const core::vector3df& scaling)
{
  btVector3 vertices[3];
  u32 i,j,k,index,numVertices,numIndices;
  u16* mb_indices;
  btTriangleMesh *pTriMesh = new btTriangleMesh();
  for (i=0; i<pMesh->getMeshBufferCount(); i++)
  {
    scene::IMeshBuffer* mb=pMesh->getMeshBuffer(i);
    if(mb->getVertexType()==video::EVT_STANDARD)
    {
      video::S3DVertex* mb_vertices=(video::S3DVertex*)mb->getVertices();
      mb_indices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      for(j=0;j<numIndices;j+=3)
      {
        for (k=0;k<3;k++)
        {
          index = mb_indices[j+k];
          vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X, mb_vertices[index].Pos.Y*scaling.Y, mb_vertices[index].Pos.Z*scaling.Z);
        }
        pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
      }
    }
    else if(mb->getVertexType()==video::EVT_2TCOORDS)
    {
      video::S3DVertex2TCoords* mb_vertices=(video::S3DVertex2TCoords*)mb->getVertices();
      mb_indices = mb->getIndices();
      numVertices = mb->getVertexCount();
      numIndices = mb->getIndexCount();
      for(j=0;j<numIndices;j+=3)
      {
        for (k=0;k<3;k++)
        {
          index = mb_indices[j+k];
          vertices[k] = btVector3(mb_vertices[index].Pos.X*scaling.X, mb_vertices[index].Pos.Y*scaling.Y, mb_vertices[index].Pos.Z*scaling.Z);
        }
        pTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
      }
    }
  }
  return pTriMesh;
};

#endif	/* BULLETCONVERSIONS_HPP */

