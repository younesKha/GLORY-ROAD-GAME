/*
writen by (Younes khafaja) - 2008-2009
You are free to use this code as you see fit
email : lighting-team@hotmail.com
*/
#include <irrlicht.h>
using namespace irr;
#ifndef MYN_H
#define MYN_H
class MyShotNode : public scene::ISceneNode
{
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;

public:

	MyShotNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id): scene::ISceneNode(parent, mgr,id)
	{
		Material.Wireframe = false;
		Material.Lighting = false;

		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		//Material.setTexture(0,driver->getTexture("shot.png"));
		video::SColor ss(0,100,100,100);
		//ss.setAlpha(0);
		
		Vertices[0] = video::S3DVertex(3,3,0, 0,0,1,ss, 0, 0);
		Vertices[1] = video::S3DVertex(3,-3,0, 0,0,1,ss, 0, 1);
		Vertices[2] = video::S3DVertex(-3,-3,0, 0,0,1,ss, 1, 1);
		Vertices[3] = video::S3DVertex(-3,3,0, 0,0,1,ss, 1, 0);
		


		Box.reset(Vertices[0].Pos);
		for (s32 i=1; i<4; ++i)
			Box.addInternalPoint(Vertices[i].Pos);
	}

	virtual void OnRegisterSceneNode()
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);
			ISceneNode::OnRegisterSceneNode();
	}

	virtual void render()
	{
		u16 indices[] = {0,1,2, 2,3,0};
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);


		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawIndexedTriangleList(&Vertices[0], 4, &indices[0], 2);

	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		return Box;
	}

	virtual u32 getMaterialCount() const
	{
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i)
	{
		return Material;
	}	
	void setRotationRAdians(core::vector3df Rotrationadians)
	{
	AbsoluteTransformation=AbsoluteTransformation.setRotationRadians(Rotrationadians);

	}

};
#endif