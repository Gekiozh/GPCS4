#pragma once
#include "GvePipelineState.h"

namespace gve
{;



GveVertexAttribute::GveVertexAttribute(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset) :
	m_location(uint32_t(location)),
	m_binding(uint32_t(binding)),
	m_format(uint32_t(format)),
	m_offset(uint32_t(offset)),
	m_reserved(0)
{

}

uint32_t GveVertexAttribute::location() const
{
	return m_location;
}

uint32_t GveVertexAttribute::binding() const
{
	return m_binding;
}

VkFormat GveVertexAttribute::format() const
{
	return VkFormat(m_format);
}

uint32_t GveVertexAttribute::offset() const
{
	return m_offset;
}

VkVertexInputAttributeDescription GveVertexAttribute::description() const
{
	VkVertexInputAttributeDescription result;
	result.location = m_location;
	result.binding = m_binding;
	result.format = VkFormat(m_format);
	result.offset = m_offset;
	return result;
}

GveVertexBinding::GveVertexBinding(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate, uint32_t divisor) :
	m_binding(uint32_t(binding)),
	m_stride(uint32_t(stride)),
	m_inputRate(uint32_t(inputRate)),
	m_reserved(0),
	m_divisor(divisor)
{

}

uint32_t GveVertexBinding::binding() const
{
	return m_binding;
}

uint32_t GveVertexBinding::stride() const
{
	return m_stride;
}

VkVertexInputRate GveVertexBinding::inputRate() const
{
	return VkVertexInputRate(m_inputRate);
}

uint32_t GveVertexBinding::divisor() const
{
	return m_divisor;
}

VkVertexInputBindingDescription GveVertexBinding::description() const
{
	VkVertexInputBindingDescription result;
	result.binding = m_binding;
	result.stride = m_stride;
	result.inputRate = VkVertexInputRate(m_inputRate);
	return result;
}

void GveVertexBinding::setStride(uint32_t stride)
{
	m_stride = stride;
}


void GveVertexInputInfo::addBinding(const GveVertexBinding& binding)
{
	m_bindings.push_back(binding);
}

void GveVertexInputInfo::addAttribute(const GveVertexAttribute& attr)
{
	m_attributes.push_back(attr);
}

VkPipelineVertexInputStateCreateInfo GveVertexInputInfo::state() const
{
	VkPipelineVertexInputStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	info.pNext = nullptr;

	std::array<VkVertexInputBindingDescription, MaxNumVertexBindings> bindings;
	uint32_t bindingCount = 0;
	for (const auto& binding : m_bindings)
	{
		bindings[bindingCount++] = binding.description();
	}

	info.vertexBindingDescriptionCount = bindingCount;
	info.pVertexBindingDescriptions = bindings.data();


	uint32_t attrCount = 0;
	std::array<VkVertexInputAttributeDescription, MaxNumVertexAttributes> attributes;
	for (const auto& attr : m_attributes)
	{
		attributes[attrCount++] = attr.description();
	}

	info.vertexAttributeDescriptionCount = attrCount;
	info.pVertexAttributeDescriptions = attributes.data();

	return info;
}

GveInputAssemblyInfo::GveInputAssemblyInfo(VkPrimitiveTopology primitiveTopology, VkBool32 primitiveRestart, uint32_t patchVertexCount) : m_primitiveTopology(uint16_t(primitiveTopology)),
m_primitiveRestart(uint16_t(primitiveRestart)),
m_patchVertexCount(uint16_t(patchVertexCount)),
m_reserved(0)
{

}

VkPrimitiveTopology GveInputAssemblyInfo::primitiveTopology() const
{
	return m_primitiveTopology <= VK_PRIMITIVE_TOPOLOGY_PATCH_LIST
		? VkPrimitiveTopology(m_primitiveTopology)
		: VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
}

VkBool32 GveInputAssemblyInfo::primitiveRestart() const
{
	return VkBool32(m_primitiveRestart);
}

uint32_t GveInputAssemblyInfo::patchVertexCount() const
{
	return m_patchVertexCount;
}

VkPipelineInputAssemblyStateCreateInfo GveInputAssemblyInfo::state() const
{
	VkPipelineInputAssemblyStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.pNext = nullptr;
	info.topology = VkPrimitiveTopology(m_primitiveTopology);
	info.primitiveRestartEnable = VkBool32(m_primitiveRestart);
	return info;
}

GveRasterizationInfo::GveRasterizationInfo(VkBool32 depthClipEnable, VkBool32 depthBiasEnable, VkPolygonMode polygonMode, VkCullModeFlags cullMode, VkFrontFace frontFace, uint32_t viewportCount, VkSampleCountFlags sampleCount) :
	m_depthClipEnable(uint32_t(depthClipEnable)),
	m_depthBiasEnable(uint32_t(depthBiasEnable)),
	m_rasterizerDiscardEnable(uint32_t(0)),
	m_polygonMode(uint32_t(polygonMode)),
	m_cullMode(uint32_t(cullMode)),
	m_frontFace(uint32_t(frontFace)),
	m_viewportCount(uint32_t(viewportCount)),
	m_sampleCount(uint32_t(sampleCount)),
	m_reserved(0)
{

}

VkBool32 GveRasterizationInfo::depthClipEnable() const
{
	return VkBool32(m_depthClipEnable);
}

VkBool32 GveRasterizationInfo::depthBiasEnable() const
{
	return VkBool32(m_depthBiasEnable);
}

VkPolygonMode GveRasterizationInfo::polygonMode() const
{
	return VkPolygonMode(m_polygonMode);
}

VkCullModeFlags GveRasterizationInfo::cullMode() const
{
	return VkCullModeFlags(m_cullMode);
}

VkFrontFace GveRasterizationInfo::frontFace() const
{
	return VkFrontFace(m_frontFace);
}

uint32_t GveRasterizationInfo::viewportCount() const
{
	return m_viewportCount;
}

VkSampleCountFlags GveRasterizationInfo::sampleCount() const
{
	return VkSampleCountFlags(m_sampleCount);
}

void GveRasterizationInfo::setViewportCount(uint32_t viewportCount)
{
	m_viewportCount = viewportCount;
}

VkPipelineRasterizationStateCreateInfo GveRasterizationInfo::state() const
{
	VkPipelineRasterizationStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	info.pNext = nullptr;
	info.depthClampEnable = VkBool32(m_depthClipEnable);
	info.rasterizerDiscardEnable = VkBool32(0);
	info.polygonMode = VkPolygonMode(m_polygonMode);
	info.cullMode = VkCullModeFlags(m_cullMode);
	info.frontFace = VkFrontFace(m_frontFace);
	info.depthBiasEnable = VkBool32(m_depthBiasEnable);
	info.depthBiasConstantFactor = m_depthBiasSlopeFactor;
	info.depthBiasClamp = m_depthBiasClamp;
	info.depthBiasSlopeFactor = m_depthBiasSlopeFactor;
	info.lineWidth = m_lineWidth;
	return info;
}

GveMultisampleInfo::GveMultisampleInfo(
	VkSampleCountFlagBits rasterizationSamples, 
	VkBool32 sampleShadingEnable, 
	float minSampleShading, 
	VkSampleMask sampleMask, 
	VkBool32 alphaToCoverageEnable, 
	VkBool32 alphaToOneEnable):
	m_rasterizationSamples(uint32_t(rasterizationSamples)),
	m_sampleShadingEnable(uint32_t(sampleShadingEnable)),
	m_alphaToCoverageEnable(uint32_t(alphaToCoverageEnable)),
	m_alphaToOneEnable(uint32_t(alphaToOneEnable)),
	m_reserved(0),
	m_sampleMask(uint32_t(sampleMask)),
	m_minSampleShading(minSampleShading)
{

}

VkSampleCountFlagBits GveMultisampleInfo::sampleCount() const
{
	return VkSampleCountFlagBits(m_rasterizationSamples);
}

VkSampleMask GveMultisampleInfo::sampleMask() const
{
	return m_sampleMask;
}

VkBool32 GveMultisampleInfo::enableAlphaToCoverage() const
{
	return VkBool32(m_alphaToCoverageEnable);
}

void GveMultisampleInfo::setSampleCount(VkSampleCountFlagBits sampleCount)
{
	m_rasterizationSamples = VkSampleCountFlagBits(sampleCount);
}

VkPipelineMultisampleStateCreateInfo GveMultisampleInfo::state() const
{
	VkPipelineMultisampleStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	info.pNext = nullptr;

	info.rasterizationSamples = VkSampleCountFlagBits(m_rasterizationSamples);
	info.sampleShadingEnable = VkBool32(m_sampleShadingEnable);
	info.alphaToCoverageEnable = VkBool32(m_alphaToCoverageEnable);
	info.alphaToOneEnable = VkBool32(m_alphaToOneEnable);
	info.pSampleMask = (VkSampleMask*)&m_sampleMask;
	info.minSampleShading = m_minSampleShading;

	return info;
}

GveDepthStencilOp::GveDepthStencilOp(VkStencilOpState state) :
	m_failOp(uint32_t(state.failOp)),
	m_passOp(uint32_t(state.passOp)),
	m_depthFailOp(uint32_t(state.depthFailOp)),
	m_compareOp(uint32_t(state.compareOp)),
	m_reserved(0),
	m_compareMask(uint32_t(state.compareMask)),
	m_writeMask(uint32_t(state.writeMask))
{

}

VkStencilOpState GveDepthStencilOp::state() const
{
	VkStencilOpState result;
	result.failOp = VkStencilOp(m_failOp);
	result.passOp = VkStencilOp(m_passOp);
	result.depthFailOp = VkStencilOp(m_depthFailOp);
	result.compareOp = VkCompareOp(m_compareOp);
	result.compareMask = m_compareMask;
	result.writeMask = m_writeMask;
	result.reference = 0;
	return result;
}

GveDepthStencilInfo::GveDepthStencilInfo(VkBool32 enableDepthTest, 
	VkBool32 enableDepthWrite, 
	VkBool32 enableDepthBoundsTest, 
	VkBool32 enableStencilTest, 
	VkCompareOp depthCompareOp,
	GveDepthStencilOp frontOp,
	GveDepthStencilOp backOp) :
	m_enableDepthTest(uint16_t(enableDepthTest)),
	m_enableDepthWrite(uint16_t(enableDepthWrite)),
	m_enableDepthBoundsTest(uint16_t(enableDepthBoundsTest)),
	m_enableStencilTest(uint16_t(enableStencilTest)),
	m_depthCompareOp(uint16_t(depthCompareOp)),
	m_reserved(0),
	m_frontOp(frontOp),
	m_backOp(backOp)
{

}

VkBool32 GveDepthStencilInfo::enableDepthTest() const
{
	return VkBool32(m_enableDepthTest);
}

VkBool32 GveDepthStencilInfo::enableDepthWrite() const
{
	return VkBool32(m_enableDepthWrite);
}

VkBool32 GveDepthStencilInfo::enableDepthBoundsTest() const
{
	return VkBool32(m_enableDepthBoundsTest);
}

VkBool32 GveDepthStencilInfo::enableStencilTest() const
{
	return VkBool32(m_enableStencilTest);
}

VkCompareOp GveDepthStencilInfo::depthCompareOp() const
{
	return VkCompareOp(m_depthCompareOp);
}

void GveDepthStencilInfo::setEnableDepthBoundsTest(VkBool32 enableDepthBoundsTest)
{
	m_enableDepthBoundsTest = VkBool32(enableDepthBoundsTest);
}

VkPipelineDepthStencilStateCreateInfo GveDepthStencilInfo::state() const
{
	VkPipelineDepthStencilStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	info.pNext = nullptr;
	
	info.depthTestEnable = VkBool32(m_enableDepthTest);
	info.depthWriteEnable = VkBool32(m_enableDepthWrite);
	info.depthCompareOp = VkCompareOp(m_depthCompareOp);
	info.depthBoundsTestEnable = VkBool32(m_enableDepthBoundsTest);
	info.stencilTestEnable = VkBool32(m_enableStencilTest);

	info.front = m_frontOp.state();
	info.back = m_backOp.state();

	info.minDepthBounds = m_minDepthBounds;
	info.maxDepthBounds = m_maxDepthBounds;

 	return info;
}

GveColorBlendAttachment::GveColorBlendAttachment(VkBool32 blendEnable, VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOp, VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp, VkColorComponentFlags colorWriteMask) :
	m_blendEnable(uint32_t(blendEnable)),
	m_srcColorBlendFactor(uint32_t(srcColorBlendFactor)),
	m_dstColorBlendFactor(uint32_t(dstColorBlendFactor)),
	m_colorBlendOp(uint32_t(colorBlendOp)),
	m_srcAlphaBlendFactor(uint32_t(srcAlphaBlendFactor)),
	m_dstAlphaBlendFactor(uint32_t(dstAlphaBlendFactor)),
	m_alphaBlendOp(uint32_t(alphaBlendOp)),
	m_colorWriteMask(uint32_t(colorWriteMask)),
	m_reserved(0)
{

}

VkBool32 GveColorBlendAttachment::blendEnable() const
{
	return m_blendEnable;
}

VkBlendFactor GveColorBlendAttachment::srcColorBlendFactor() const
{
	return VkBlendFactor(m_srcColorBlendFactor);
}

VkBlendFactor GveColorBlendAttachment::dstColorBlendFactor() const
{
	return VkBlendFactor(m_dstColorBlendFactor);
}

VkBlendOp GveColorBlendAttachment::colorBlendOp() const
{
	return VkBlendOp(m_colorBlendOp);
}

VkBlendFactor GveColorBlendAttachment::srcAlphaBlendFactor() const
{
	return VkBlendFactor(m_srcAlphaBlendFactor);
}

VkBlendFactor GveColorBlendAttachment::dstAlphaBlendFactor() const
{
	return VkBlendFactor(m_dstAlphaBlendFactor);
}

VkBlendOp GveColorBlendAttachment::alphaBlendOp() const
{
	return VkBlendOp(m_alphaBlendOp);
}

VkColorComponentFlags GveColorBlendAttachment::colorWriteMask() const
{
	return VkColorComponentFlags(m_colorWriteMask);
}

VkPipelineColorBlendAttachmentState GveColorBlendAttachment::state() const
{
	VkPipelineColorBlendAttachmentState result;
	result.blendEnable = VkBool32(m_blendEnable);
	result.srcColorBlendFactor = VkBlendFactor(m_srcColorBlendFactor);
	result.dstColorBlendFactor = VkBlendFactor(m_dstColorBlendFactor);
	result.colorBlendOp = VkBlendOp(m_colorBlendOp);
	result.srcAlphaBlendFactor = VkBlendFactor(m_srcAlphaBlendFactor);
	result.dstAlphaBlendFactor = VkBlendFactor(m_dstAlphaBlendFactor);
	result.alphaBlendOp = VkBlendOp(m_alphaBlendOp);
	result.colorWriteMask = VkColorComponentFlags(m_colorWriteMask);
	return result;
}

GveColorBlendInfo::GveColorBlendInfo(VkBool32 logicOpEnable, VkLogicOp logicOp):
	m_logicOp(uint32_t(logicOp)),
	m_logicOpEnable(uint32_t(logicOpEnable)),
	m_reserved(0)
{

}

void GveColorBlendInfo::addAttachment(GveColorBlendAttachment attachment)
{
	m_attachments.push_back(attachment);
}

void GveColorBlendInfo::setBlendConstants(float constants[4])
{
	std::memcpy(m_blendConstants, constants, sizeof(float) * 4);
}

VkPipelineColorBlendStateCreateInfo GveColorBlendInfo::state() const
{
	VkPipelineColorBlendStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	info.logicOpEnable = VkBool32(m_logicOpEnable);
	info.logicOp = VkLogicOp(m_logicOp);

	std::array<VkPipelineColorBlendAttachmentState, MaxNumRenderTargets> attachments;
	uint32_t attachmentCount = 0;
	for (const auto& atc : m_attachments)
	{
		attachments[attachmentCount++] = atc.state();
	}

	info.attachmentCount = attachmentCount;
	info.pAttachments = attachments.data();

	info.blendConstants[0] = m_blendConstants[0];
	info.blendConstants[1] = m_blendConstants[1];
	info.blendConstants[2] = m_blendConstants[2];
	info.blendConstants[3] = m_blendConstants[3];
	return info;
}

}  // namespace gve