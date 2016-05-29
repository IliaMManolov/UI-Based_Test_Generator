template <typename T>
    std::wstring toString(const T& value)
    {
        std::wstringstream stream;
        stream << value;
        return stream.str();
    }

template <typename T>
    T toValue(const std::wstring& str)
    {
        std::wstringstream stream;
        T tmp;
        stream << str;
        stream >> tmp;
        return tmp;
    }
