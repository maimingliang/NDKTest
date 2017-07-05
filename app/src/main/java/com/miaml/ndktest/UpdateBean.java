package com.miaml.ndktest;

/**
 * 类       名:
 * 说       明:
 * 修 改 记 录:
 * 版 权 所 有:   Copyright © 2017
 * 公       司:   深圳市旅联网络科技有限公司
 * version   0.1
 * date   2017/7/5
 * author   maimingliang
 */


public class UpdateBean {


    /**
     * code : ELK_000000
     * data : {"versionNumber":"3.0.0","introduction":"测试","way":0,"fileInfoExt":{"fullFileName":"app-debug.apk","fullPath":"group1/M00/00/A9/wKgA6Flcmg2ATPf3ABn3Sx2RIMI921.apk"},"updateFlag":1}
     */

    private String code;
    private DataBean data;

    public String getCode() {
        return code;
    }

    public void setCode(String code) {
        this.code = code;
    }

    public DataBean getData() {
        return data;
    }

    public void setData(DataBean data) {
        this.data = data;
    }

    public static class DataBean {
        /**
         * versionNumber : 3.0.0
         * introduction : 测试
         * way : 0
         * fileInfoExt : {"fullFileName":"app-debug.apk","fullPath":"group1/M00/00/A9/wKgA6Flcmg2ATPf3ABn3Sx2RIMI921.apk"}
         * updateFlag : 1
         */

        private String versionNumber;
        private String introduction;
        private int way;
        private FileInfoExtBean fileInfoExt;
        private int updateFlag;

        public String getVersionNumber() {
            return versionNumber;
        }

        public void setVersionNumber(String versionNumber) {
            this.versionNumber = versionNumber;
        }

        public String getIntroduction() {
            return introduction;
        }

        public void setIntroduction(String introduction) {
            this.introduction = introduction;
        }

        public int getWay() {
            return way;
        }

        public void setWay(int way) {
            this.way = way;
        }

        public FileInfoExtBean getFileInfoExt() {
            return fileInfoExt;
        }

        public void setFileInfoExt(FileInfoExtBean fileInfoExt) {
            this.fileInfoExt = fileInfoExt;
        }

        public int getUpdateFlag() {
            return updateFlag;
        }

        public void setUpdateFlag(int updateFlag) {
            this.updateFlag = updateFlag;
        }

        public static class FileInfoExtBean {
            /**
             * fullFileName : app-debug.apk
             * fullPath : group1/M00/00/A9/wKgA6Flcmg2ATPf3ABn3Sx2RIMI921.apk
             */

            private String fullFileName;
            private String fullPath;

            public String getFullFileName() {
                return fullFileName;
            }

            public void setFullFileName(String fullFileName) {
                this.fullFileName = fullFileName;
            }

            public String getFullPath() {
                return fullPath;
            }

            public void setFullPath(String fullPath) {
                this.fullPath = fullPath;
            }
        }
    }
}
