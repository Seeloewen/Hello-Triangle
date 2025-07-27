struct Input
{
    float3 position : POSITION0;
    float3 color : COLOR0;
};

struct Output
{
    float4 position : SV_Position0;
    float3 color : COLOR0;
};

Output Main(Input input)
{
    Output output;
    output.position = float4(input.position, 1.0);
    output.color = input.color;
    return output;
}