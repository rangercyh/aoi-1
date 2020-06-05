local aoi = require "aoi"
local MAKER_MARK = aoi.MAKER_MARK
local WATCHER_MARK = aoi.WATCHER_MARK

local aoi_obj = aoi.aoi_new(10, 20, 3, 3)

print(aoi, aoi_obj, MAKER_MARK, WATCHER_MARK)
for k, v in pairs(getmetatable(aoi_obj)) do
    print(k, v)
end
