package com.miaml.ndktest;

/**
 * author   maimingliang
 */


public class HelloNDK {


    public static native void fileEncrypt(String normalFilePath, String encryptFilePath, String password);

    public static native void fileDecrypt(String encryptFilePath, String decryptFilePath, String password);

    public static native void splitFile(String filePath,String suffix,int splitFileNum);

    public static native void mergeFile(String filePath,String mergeFilePath,String suffix,String mergeSuffix,int splitNum);


    static {
        System.loadLibrary("native-lib");
    }
}
