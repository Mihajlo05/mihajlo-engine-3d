#pragma once

#include <vector>
#include "Math/MihajloMath.h"
#include "Graphics/Graphics.h"

//Was lazy to seperate code in .h and .cpp files, so it's all in this file

namespace DynamicVertexBuf
{
	struct BGRAColorData //in case we are making colors with unsigned char (0-255) values
	{
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	class VertexLayout //Describes the layout of Vertex, type of each element and it's offset in memory from beginning of Vertex
	{
	public:
		enum ElementType
		{
			Position3D,
			Position2D,
			Texture2D,
			Normal,
			Float3Color, //without alpha channel
			Float4Color, //with alpha channel
			BGRAColor,
			Count
		};
	public:
		template<ElementType> struct Map; //From this, you can get usefull information about each element type
		template<> struct Map<Position3D>
		{
			using SysType = float3; //this is actuall, system type that is being used for this type
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "POSITION"; //semantic that is being used in shaders
			static constexpr const char* code = "P3";
		};
		template<> struct Map<Position2D>
		{
			using SysType = float2;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32_FLOAT;
			static constexpr const char* semantic = "POSITION";
			static constexpr const char* code = "P2";
		};
		template<> struct Map<Texture2D>
		{
			using SysType = float2;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "TEXCOORD";
			static constexpr const char* code = "T2";
		};
		template<> struct Map<Normal>
		{
			using SysType = float3;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "NORMAL";
			static constexpr const char* code = "N";
		};
		template<> struct Map<Float3Color>
		{
			using SysType = float3;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32_FLOAT;
			static constexpr const char* semantic = "COLOR";
			static constexpr const char* code = "F3C";
		};
		template<> struct Map<Float4Color>
		{
			using SysType = float4;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;
			static constexpr const char* semantic = "COLOR";
			static constexpr const char* code = "F4C";
		};
		template<> struct Map<BGRAColor>
		{
			using SysType = DynamicVertexBuf::BGRAColorData;
			static constexpr DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			static constexpr const char* semantic = "COLOR";
			static constexpr const char* code = "BGRAC";
		};
	public:
		class Element //Describes one element of vertex
		{
		public:
			Element(ElementType type, size_t offset) : type(type), offset(offset) {}
			ElementType GetType() const { return type; }
			size_t GetOffset() const { return offset; }
			size_t GetOffsetAfter() const
			{
				return offset + Size();
			}
			size_t Size() const
			{
				return SizeOf(type);
			}
			static constexpr size_t SizeOf(ElementType type)
			{
				switch (type)
				{
				case Position2D:
					return sizeof(Map<Position2D>::SysType);
				case Position3D:
					return sizeof(Map<Position3D>::SysType);
				case Texture2D:
					return sizeof(Map<Texture2D>::SysType);
				case Normal:
					return sizeof(Map<Normal>::SysType);
				case Float3Color:
					return sizeof(Map<Float3Color>::SysType);
				case Float4Color:
					return sizeof(Map<Float4Color>::SysType);
				case BGRAColor:
					return sizeof(Map<BGRAColor>::SysType);
				}
				assert("Invalid element type" && false);
				return 0u;
			}
			D3D11_INPUT_ELEMENT_DESC GetDesc() const
			{
				switch (type)
				{
				case Position3D:
					return GenerateDesc<Position3D>(offset);
				case Position2D:
					return GenerateDesc<Position2D>(offset);
				case Texture2D:
					return GenerateDesc<Texture2D>(offset);
				case Normal:
					return GenerateDesc<Normal>(offset);
				case Float3Color:
					return GenerateDesc<Float3Color>(offset);
				case Float4Color:
					return GenerateDesc<Float4Color>(offset);
				case BGRAColor:
					return GenerateDesc<BGRAColor>(offset);
				default:
					return {};
				}
			}
			const char* GetCode() const
			{
				switch (type)
				{
				case Position3D:
					return Map<Position3D>::code;
				case Position2D:
					return Map<Position2D>::code;
				case Texture2D:
					return Map<Texture2D>::code;
				case Normal:
					return Map<Normal>::code;
				case Float3Color:
					return Map<Float3Color>::code;
				case Float4Color:
					return Map<Float4Color>::code;
				case BGRAColor:
					return Map<BGRAColor>::code;
				default:
					assert(false);
					return "";
				}
			}
		private:
			template<ElementType Type>
			static constexpr D3D11_INPUT_ELEMENT_DESC GenerateDesc(size_t offset)
			{
				return { Map<Type>::semantic, 0, Map<Type>::dxgiFormat, 0u, (UINT)offset, D3D11_INPUT_PER_VERTEX_DATA, 0u };
			}
		private:
			ElementType type;
			size_t offset;
		};
	public:
		VertexLayout() = default;
		const Element& GetElement(ElementType type) const
		{
			for (auto& e : elements)
			{
				if (e.GetType() == type)
				{
					return e;
				}
			}
			assert(false);
			return elements.front();
		}
		const Element& GetElementByIndex(size_t index) const
		{
			return elements[index];
		}
		VertexLayout& Append(ElementType type)
		{
			elements.emplace_back(type, Size());
			return *this;
		}
		size_t Size() const
		{
			return elements.empty() ? 0u : elements.back().GetOffsetAfter();
		}
		size_t GetElementCount() const
		{
			return elements.size();
		}
		std::vector<D3D11_INPUT_ELEMENT_DESC> GetD3DLayout() const
		{
			std::vector<D3D11_INPUT_ELEMENT_DESC> d3dl;

			for (const Element& e : elements)
			{
				d3dl.push_back(e.GetDesc());
			}

			return d3dl;
		}
		std::string GetCode() const
		{
			std::string code;

			for (const Element& e : elements)
			{
				code += e.GetCode();
			}
			return code;
		}
	private:
		std::vector<Element> elements;
	};

	class Vertex
	{
		friend class VertexBuffer;
	public:
		Vertex(VertexLayout& layout, char* pData) : layout(layout), pData(pData) { }
		template<VertexLayout::ElementType Type>
		auto& Attribute()
		{
			const VertexLayout::Element& element = layout.GetElement(Type);
			char* pAttribute = pData + element.GetOffset();
			return *reinterpret_cast<VertexLayout::Map<Type>::SysType*>(pAttribute);
		}
		template<typename T>
		void SetAttrByIndex(size_t i, T&& val)
		{
			const VertexLayout::Element& element = layout.GetElementByIndex(i);
			char* pAttribute = pData + element.GetOffset();

			switch (element.GetType())
			{
			case VertexLayout::Position2D:
				SetAttribute<VertexLayout::Position2D>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::Position3D:
				SetAttribute<VertexLayout::Position3D>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::Texture2D:
				SetAttribute<VertexLayout::Texture2D>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::Normal:
				SetAttribute<VertexLayout::Normal>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::Float3Color:
				SetAttribute<VertexLayout::Float3Color>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::Float4Color:
				SetAttribute<VertexLayout::Float4Color>(pAttribute, std::forward<T>(val));
				break;
			case VertexLayout::BGRAColor:
				SetAttribute<VertexLayout::BGRAColor>(pAttribute, std::forward<T>(val));
				break;
			default:
				assert("Bad element type" && false);
			}
		}
	private:
		template<typename First, typename... Rest>
		void SetAttrByIndex(size_t i, First&& first, Rest&&... rest) //setting all attributes after index
		{
			SetAttrByIndex(i, std::forward<First>(first)); //setting the first attribute, goes to overload of this function
			SetAttrByIndex(i + 1, std::forward<Rest>(rest)...); //setting the rest of attributes (recursion)
		}
		template<VertexLayout::ElementType Dest, typename Src>
		void SetAttribute(char* pAttr, Src&& val)
		{
			using D = typename VertexLayout::Map<Dest>::SysType;
			if constexpr (std::is_assignable<D, Src>::value)
			{
				*reinterpret_cast<D*>(pAttr) = val;
			}
			else
			{
				assert("Parameter attribute type mismatch" && false);
			}
		}
	private:
		char* pData;
		VertexLayout& layout;
	};

	class ConstVertex
	{
	public:
		ConstVertex(const Vertex data) : data(data) {}
		template<VertexLayout::ElementType Type>
		const auto& Attribute() const
		{
			return const_cast<Vertex&>(data).Attribute<Type>();
		}
	private:
		Vertex data;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(VertexLayout layout) : layout(std::move(layout)) {}
		const VertexLayout& GetLayout() const { return layout; }
		size_t Size() const // size in vertices
		{
			return SizeInBytes() / layout.Size();
		}
		size_t SizeInBytes() const
		{
			return buffer.size();
		}
		template<typename... Params>
		void EmplaceBack(Params&&... params)
		{
			assert(sizeof...(params) == layout.GetElementCount());
			buffer.resize(SizeInBytes() + layout.Size());
			Back().SetAttrByIndex(0, std::forward<Params>(params)...);
		}
		Vertex Back()
		{
			assert(Size() != 0);
			return Vertex(layout, buffer.data() + SizeInBytes() - layout.Size());
		}
		ConstVertex CBack() const
		{
			return const_cast<VertexBuffer&>(*this).Back();
		}
		ConstVertex Back() const
		{
			return CBack();
		}
		Vertex Front()
		{
			assert(Size() != 0);
			return Vertex(layout, buffer.data());
		}
		ConstVertex CFront() const
		{
			return const_cast<VertexBuffer&>(*this).Front();
		}
		ConstVertex Front() const
		{
			return CFront();
		}
		Vertex operator[](size_t i)
		{
			assert(i < Size());
			return Vertex(layout, buffer.data() + layout.Size() * i);
		}
		char* GetData()
		{
			return buffer.data();
		}
		const char* GetData() const
		{
			return buffer.data();
		}
	private:
		VertexLayout layout; //this describes Vertices in buffer
		std::vector<char> buffer; //array of bites for data
	};
}