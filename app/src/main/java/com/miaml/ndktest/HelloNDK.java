package com.miaml.ndktest;

/**
 * 类       名:
 * 说       明:
 * 修 改 记 录:
 * 版 权 所 有:   Copyright © 2017
 * 公       司:   深圳市旅联网络科技有限公司
 * version   0.1
 * date   2017/7/4
 * author   maimingliang
 */


public class HelloNDK {


    public static native void fileEncrypt(String normalFilePath, String encryptFilePath, String password);

    public static native void fileDecrypt(String encryptFilePath, String decryptFilePath, String password);

    public static native void splitFile(String filePath,String suffix,int splitFileNum);


    static {
        System.loadLibrary("native-lib");
    }
}
