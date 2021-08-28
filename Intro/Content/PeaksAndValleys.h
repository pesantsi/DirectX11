#pragma once

#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace Intro
{
	class PeaksAndValleys
	{
	public:
		PeaksAndValleys(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();

	private:
		uint32 mNumRows;
		uint32 mNumCols;

		uint32 mNumVertices;
		uint32 mNumFaces;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IB;
	};
}