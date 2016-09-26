RWBuffer<uint> dummyUAV;
cbuffer dummyCB
{
	uint zero;
}
[numthreads(256, 1, 1)]
void main(uint3 id : SV_DispatchThreadID)
{
    [loop]
	while (zero == 0)
		dummyUAV[id.x] = zero;
}