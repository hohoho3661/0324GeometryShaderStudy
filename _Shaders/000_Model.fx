//-----------------------------------------------------------------------------
// Bones
//-----------------------------------------------------------------------------
#define MODEL_MAX_TRANSFORMS 128

cbuffer CB_Bone
{
    matrix BoneTransforms[MODEL_MAX_TRANSFORMS];

    uint Index;
};

void SetModelWorld(inout matrix world) // inout = 레퍼런스,,, 참조,, 받기도하고 리턴도 할거임
{
    world = mul(BoneTransforms[Index], world);
}