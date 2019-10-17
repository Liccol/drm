-- lua坑
-- 查询str长度可以直接使用#号

-- global
licenseStorage = {
    index,
    content,
    object,
    key,
    keyRules,
    signature
}
tmpStorage = {
    typeL,
    index,
    length,
    data
}
switch = {
    ["00"] = "index",
    ["01"] = "content",
    ["02"] = "object",
    ["03"] = "key",
    ["04"] = "keyRules",
    ["FF"] = "signature"
}

function hex2num(hexInput)
    local numReturn = tonumber(hexInput, 16)
    return numReturn
end
-- TODO: 许可证解析规模扩大, 使用table套table的模式
-- TODO: 可以存一个enum,方便直接用文本代替取值,增加易读性
-- TODO: 抽象出一个接口AnalyzeType(StringInput,Type),
-- 对应licenseStorage.Type.*各段存下去
-- 代码结构:
-- 初始化一些值flag,Length
-- 取当前字符串的第一个,即Type,判断索引的内容,进入一个switch
-- switch中通过Type,进行AnalyzeType(剩余字符串,要存Type)
-- AnalyzeType可以在开始再多一个判断,确保进入的string是对的

-- table对象打印
-- @function: 获取table的字符串格式内容，递归
-- @tab： table
-- @ind：不用传此参，递归用（前缀格式（空格））
-- @return: format string of the table
function dumpTab(tab,ind)
    if (tab == nil) then return "nil" end;
    local str = "{";
    if (ind == nil) then ind="  "; end;
    --//each of table
    for k, v in pairs(tab) do
        --//key
        if (type(k)=="string") then
            k = tostring(k).." = ";
        else
            k = "["..tostring(k).."] = ";
        end;--//end if
        --//value
        local s="";
        if (type(v) == "nil") then
            s="nil";
        elseif (type(v) == "boolean") then
            if (v) then s = "true"; else s = "false"; end;
        elseif (type(v) == "number")then
            s = v;
        elseif (type(v) == "string")then
            s = "\""..v.."\"";
        elseif (type(v) == "table")then
            s = dumpTab(v,ind.."  ");
            s = string.sub(s,1,#s-1);
        elseif (type(v) == "function")then
            s = "function : "..v;
        elseif (type(v) == "thread")then
            s = "thread : "..tostring(v);
        elseif (type(v) == "userdata")then
            s = "userdata : "..tostring(v);
        else
            s = "nuknow : "..tostring(v);
        end;
        -- Contact
        str = str.."\n"..ind..k..s.." ,";
    end
    --//return the format string
    local sss = string.sub(str,1,#str-1);
    if (#ind > 0) then ind = string.sub(ind,1,#ind-2) end;
    sss = sss.."\n"..ind.."}\n";
    return sss;--string.sub(str,1,#str-1).."\n"..ind.."}\n";
end

-- 查询CPU序列号
function checkCPUId()
    local cpuid=os.execute("wmic CPU get ProcessorID");
end

-- 查询type类型是否正确
function checkType(typeValue)
    local typeRt;
    typeRt = switch[typeValue];
    return typeRt;
end

-- 许可证解析
function LicenseAnalyze(licenseInput)
    -- licenseInput is hex
    print("input is", licenseInput);
    tmpString = licenseInput;
    -- 当tmpString不是空时,一直取Type判断,添加进表内容,返回数据长度,AnalyzeType结束后tmp重新赋值
    while (#tmpString ~= 0)
    do
        print("now analyze", tmpString);
        typeValue = string.sub(tmpString, 1, 2);
        typeGet = checkType(typeValue);
        if typeGet == nil then
            print('Type not included.');
            return -1;
        end
        print("Type is",typeGet);
        local returnLength = AnalyzeType(tmpString, typeGet);
        if returnLength == -1 then
            print("Analyze error.");
            return -1;
        else
            tmpString = string.sub(tmpString, returnLength / 4 + 1);
        end
    end
    print("analyze done!");
    return;
end

function AnalyzeType(stringInput, typeIndex)
    local flag = 1;
    local lenData = 0;
    local tmpStorage = {};
    -- check: string has Type/Content/Length/Data
    if #stringInput < 8 then
        print('Input String is too short.');
        return -1;
    end
    -- check: Type is the same as typeIndex
    if (switch[string.sub(stringInput, flag, flag + 1)] ~= typeIndex) then
        print('Input String is not', typeIndex, 'Type.');
        return -1;
    else
        -- save type,8 bits
        tmpStorage.typeL = string.sub(stringInput, flag, flag + 1);
        print("Type is", tmpStorage.typeL);
        if tmpStorage.typeL == "" then
            return -1;
        end
        -- save Index,8 bits
        flag = flag + 2;
        tmpStorage.index = string.sub(stringInput, flag, flag + 1);
        print("Index is", tmpStorage.index);
        -- save Length, 16 bits
        flag = flag + 2;
        tmpStorage.length = string.sub(stringInput, flag, flag + 3);
        local lenAll = tonumber(tmpStorage.length, 16);
        if lenAll%8 ~= 0 then
            print("data length is not N * 8.");
            return -1;
        end
        if lenAll <=32 then
            print("length <= 32 bits.");
            return -1;
        end
        lenData = lenAll - 8 - 8 - 16;
        print("Length code is", tmpStorage.length, ", Full length is", lenAll, "btis, Data length is", lenData, "bits");
        flag = flag + 4;
        -- save data, N * 8 bits
        tmpStorage.data = string.sub(stringInput, flag, flag + lenData / 8);
        print("Data is", tmpStorage.data);
        flag = flag + lenData / 8;
        -- check: analyze end
        if flag == lenAll / 4 then
            print(typeIndex,"analyze done.");
        else
            print(typeIndex,"analyze not done.");
        end
        licenseStorage[typeIndex] = tmpStorage;
        return lenAll;
    end
end


LicenseAnalyze("01010028FF02020028FE03030028FD04040028FCFF080028FA05050028FB");
print(dumpTab(licenseStorage));
-- LicenseAnalyze("01010000");