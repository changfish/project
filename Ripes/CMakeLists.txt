# 增加新的檔案
set(CACHE_SIM_SOURCES
    l1cacheshim.cpp
    l2cache.cpp # 新增 L2Cache 的檔案
)

set(CACHE_SIM_HEADERS
    l1cacheshim.h
    l2cache.h # 新增 L2Cache 的檔案
)

# 創建 Ripes 的 library 並加入新的檔案
create_ripes_lib(cachesim LINK_TO_RIPES_LIB SOURCES ${CACHE_SIM_SOURCES} HEADERS ${CACHE_SIM_HEADERS})
