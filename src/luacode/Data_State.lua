-- constant defination

-- RSA_Sign_val
CDRMR_RSA_Sign_Algorithm = {
	CDRMR_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1  = 0x01, 
	CDRMR_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256= 0x02,
	CDRMR_ALG_RSASSA_PKCS1_V1_5_SHA1      = 0x03,
	CDRMR_ALG_RSASSA_PKCS1_V1_5_SHA256     =0x04,
}

-- RSA_crypto_mode
CDRMR_RSA_Crypto_Algorithm = {
    CDRMR_ALG_RSA_NOPAD                    = 0x01,
	CDRMR_ALG_RSAES_PKCS1_V1_5             = 0x02,
	CDRMR_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1   = 0x03,
	CDRMR_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256 = 0x04,
}

-- Symmetric_Crypto
CDRMR_Symmetric_Crypto_Algorithm = {
	CDRMR_ALG_SM4_CBC_NOPAD     = 0x01,
	CDRMR_ALG_SM4_CTR           = 0x02,
	CDRMR_ALG_AES_128_CBC_NOPAD = 0x03,
	CDRMR_ALG_AES_128_CTR       = 0x04,
	CDRMR_ALG_AES_256_CBC_NOPAD = 0x05,
	CDRMR_ALG_AES_256_CTR       = 0x06,
	CDRMR_ALG_SM4_ECB_NOPAD     = 0x07,
	CDRMR_ALG_AES_128_ECB_NOPAD = 0x08,
	CDRMR_ALG_AES_256_ECB_NOPAD = 0x09,
	CDRMR_ALG_AES_WRAP          = 0x0a,
	CDRMR_ALG_AES_UNWRAP        = 0x0b,
}

-- HASH
CDRMR_HASH_Algorithm = {
	CDRMR_ALG_SM3   = 0x01,
	CDRMR_ALG_SHA1  = 0x02,
	CDRMR_ALG_SHA256= 0x03,
}

-- HMAC
CDRMR_HMAC_Algorithm = {
	CDRMR_ALG_HMAC_SM3   = 0x01,
	CDRMR_ALG_HMAC_SHA1  = 0x02,
	CDRMR_ALG_HMAC_SHA256= 0x03,
}

-- CENC
CDRMR_Cenc_Algorithm = {
	CDRMR_ALG_CENC_AES_CTR  = 0x01,
	CDRMR_ALG_CENC_AES_CBC  = 0x02,
	CDRMR_ALG_CENC_SM4_CTR  = 0x03,
	CDRMR_ALG_CENC_SM4_CBC  = 0x04,
}

-- storeage type
CDRMR_Storage_Type = {
	CDRMR_STORAGE_PRIVATE= 0x01,
	CDRMR_STORAGE_RESERVED=0x02,
}

-- storage access
CDRMR_Storage_Data_Access_Flag = {
	CDRMR_STORAGE_DATA_ACCESS_READ       = 0x01,
	CDRMR_STORAGE_DATA_ACCESS_WRITE      = 0x02,
	CDRMR_STORAGE_DATA_ACCESS_REMOVE     = 0x04,
	CDRMR_STORAGE_DATA_ACCESS_OVERWRITE  = 0x08,
	CDRMR_STORAGE_DATA_ACCESS_SHARE_READ = 0x10,
	CDRMR_STORAGE_DATA_ACCESS_SHARE_WRITE= 0x20,
}

licenseStorage = {}

-- TODO: LicenseAnaly函数构建
-- TODO: 需要添加全局变量保存么？
-- string2num函数可以使用，输入一个string，函数转为数字，通过这个把8位字符串转为数字？
function LicenseAnalyze(licenseInput)

end


--[[function GetLicenseRequest(
				unsigned char* pu8DrmInfo,
	            unsigned int u32DrmInfoLen,
	            unsigned char* pu8LicenseRequest,
	            unsigned int* pu32LicenseRequestLen)]]
function GetLicenseRequest(pu8DrmInfo, u32DrmInfoLen,
						   pu8LicenseRequest, pu32LicenseRequestLen)

	-- 判断Drm信息是否与长度符合符合后
	print(string.len(pu8DrmInfo))
	if (string.len(pu8DrmInfo) ~= u32DrmInfoLen)
	then
		print("u32DrmInfoLen error!")
	else
		-- check DrmInfo, 修改pu8licenseRequest的值就好
		LicenseAnalyze(pu8DrmInfo)
	end
	return 1
end



-- 实现switch函数
function switch( ... )
	-- body
	local SWITCH_METATABLE = {
		__index = function(t, k) 
		return rawget(t, "__default")
	end,
	}

end
function SwitchGenerator(tbl)
	tbl = tbl or {}
	setmetatable(tbl, SWITCH_METATABLE)
	return function(case)
		return tbl[case]()
	end, tbl
end
function NameSelect()
	local ET_CASE_ONE = 0x01
	local ET_CASE_TWO = 0x02
	local ET_CASE_THREE = 0x03
	local ET_CASE_FOUR = 0x04
	local ET_CASE_FIVE = 0xFF
 
	local function do_case_one( ... )
		print("Content Finded.")

	end
	local function do_case_two( ... )
		print("Object Finded.")
	
	end
	local function do_case_three( ... )
		print("Key Finded.")

	end
	local function do_case_four( ... )
		print("Key Rules Finded.")
		
	end
	local function do_case_five( ... )
		print("Signature Finded.")
		
	end
	local function do_default() 
		print("Default Type")
	end
 
	local switch, tbl = SwitchGenerator({
		[ET_CASE_ONE] = do_case_one,
		[ET_CASE_TWO] = do_case_two,
		[ET_CASE_THREE] = do_case_three,
		[ET_CASE_FOUR] = do_case_four,
		[ET_CASE_FIVE] = do_case_five,
		__default = do_default,
	})
	local function realTest()
		for i=1,3 do
			switch(i)
		end
	end

	realTest()
 
	tbl[3] = function() print("new add case") end
 
	realTest()
end










function ProcessLicenseResponse(pu8LicenseResponse, u32LicenseResponseLen)
	-- 解析许可证内容
	-- body
	--实现switch函数
	--Lua数据格式转换


	local result = 1
	local LicenseTable = {}

	if (string.len(pu8LicenseResponse) ~= u32LicenseResponseLen) then
		return result
	else
		{
			-- 存储字符串信息,8位存一次--需要改为1位存一次嘛？--换,配合len使用方便,字符串改hex串？
			len_8bits = u32LicenseResponseLen / 8
			for i = 1, len_8bits do
				License[i] = string.strsub(pu8LicenseRequest, i, i+8)
				-- 将数组中的字符转为数字


			end
			-- 确认许可证单元信息
			Index_Type = License[1]
			if( Index_Type ~= 0) then
				print("License index error!")
			else
				{
					Index_Length = License[3]..License[4]
					Index_Version = License[5]
					Index_LicenseID = License[6]..License[7]..License[8]..License[9]..License[10]..License[11]..License[12]..License[13]
					Index_UnitsNumber = License[14]
					Index_TimeStamp = License[15]..License[16]..License[17]..License[18]
					LicenseTable[1] = {Index_Type, Index_Length, Index_Version, Index_LicenseID, 
											Index_UnitsNumber, Index_TimeStamp};
				}
			-- 指定已查找的的单元数目
			UnitsNumberFlag = 1;
			-- 从第19个数据进行各单元内容搜寻
			BeginAnchor = 19;
			while(UnitsNumberFlag != Index_UnitsNumber) do --起始条件要改
				{
					-- 截取字符串信息,存于table中
					License[BeginAnchor]










					BeginAnchor
				}
			



			result = 0
		}
	return result
end


-- 结构体交互,用table来保存结构体
function CheckRightsStatus( ... )
	-- body
end
function Decrypt( ... )
	-- body
end
function Cenc_Decrypt( ... )
	-- body
end
function GetDeviceId( ... )
	-- body
end
function GetDrmId( ... )
	-- body
end