//
// Created by HS on 2017/6/30.
//

#include "key-lib.h"

#include "jni.h"
#include "string.h"
#include "android/log.h"
#include "stdio.h"
#include "stdlib.h"
#define LOGE(TAG,FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,__VA_ARGS__)


/**
 * 这两个函数参数类型jobject与jclass有什么区别呢 ？ 这两个类型表示 ， Java的native函数 ， 是成员方法还是类方法
 */

JNIEXPORT
jstring JNICALL Java_com_miaml_ndktest_MainActivity_getAppkey(JNIEnv *env ,jclass type){


    char* app_key = "12456789";

    return (*env)->NewStringUTF(env, app_key);

}


JNIEXPORT void JNICALL
Java_com_miaml_ndktest_MainActivity_accessJaveStringField(JNIEnv *env, jobject instance) {

    // 得到jclass
    jclass  jclazz = (*env)->GetObjectClass(env,instance);
//    // jfieldID
    jfieldID  jfid = (*env)->GetFieldID(env,jclazz,"name","Ljava/lang/String;");
    // 得到该字段的值
//
    jstring  jstr = (*env)->GetObjectField(env,instance,jfid);

    char * str = (*env)->GetStringUTFChars(env,jstr,0);

    char* text = "ssss";
//    strcat(text,str);

    jstring jnewName = (*env)->NewStringUTF(env,text);

    // 改变字段的值
    (*env)->SetObjectField(env,instance,jfid,jnewName);


}

JNIEXPORT
void JNICALL Java_com_miaml_ndktest_MainActivity_printlog(JNIEnv *env ,jclass type,jstring str_){


    const char * str = (*env) -> GetStringUTFChars(env,str_,0);

    //TODO: 显示Android 的日志
    // 调用Android的代码
    // 代码需要调用系统的日志库, 这个库已经在 CMakeList.txt添加了e,因此可以直接调用

    const char *tag = "MainActivity";
    jboolean b = JNI_FALSE;


    const char * txt = (*env) -> GetStringUTFChars(env,str_,b);

    __android_log_write(ANDROID_LOG_DEBUG,tag,txt);

    (*env) -> ReleaseStringUTFChars(env,str_,str);




}

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_MainActivity_accessJavaMethod(JNIEnv *env, jobject instance) {

    // TODO

    jclass jclazz = (*env)->GetObjectClass(env, instance);

    jmethodID jmId = (*env)->GetMethodID(env, jclazz, "print", "(I)V");


      (*env)->CallVoidMethod(env, instance, jmId, 100);

//    printf(" num = %d \n",num);

}


JNIEXPORT jlong JNICALL
Java_com_miaml_ndktest_MainActivity_accessConstructorMethod(JNIEnv *env, jobject jobj) {

    // TODO

    jclass jdatecls = (*env) -> FindClass(env,"java/util/Date");

    //得到构造器方法id
    jmethodID jmid = (*env)->GetMethodID(env, jdatecls, "<init>", "()V");

    //创建对象 更加构造器

    jobject dateObj = (*env)->NewObject(env, jdatecls, jmid);

    //调用date 的getTime()方法

    jmethodID jgetTimeMid = (*env)->GetMethodID(env,jdatecls,"getTime","()J");

    jlong time = (*env)->CallLongMethod(env, dateObj, jgetTimeMid);

    return time;



}

JNIEXPORT jstring JNICALL
Java_com_miaml_ndktest_MainActivity_cTransfrom(JNIEnv *env, jobject instance, jstring str_) {

    const char *str = (*env)->GetStringUTFChars(env, str_, 0);
    // TODO

    jint jsize = (*env)->GetStringLength(env, str_);

    printf("传进来的的值 = %s \n",str_);
    printf("大小 %d \n",jsize);


    char buff[50] = "拉啦 20";

    jclass stringCls = (*env)->FindClass(env,"java/lang/String");

    jmethodID stringInitId = (*env)->GetMethodID(env,stringCls,"<init>","([BLjava/lang/String;)V");

    //构建一个50的byte数组

   jbyteArray bytes = (*env)->NewByteArray(env,50);

    (*env)->SetByteArrayRegion(env,bytes,0,strlen(buff),buff);

    jstring charsetName = (*env)->NewStringUTF(env,"GBK");

    jstring stringTransFrom = (*env)->NewObject(env,stringCls,stringInitId,bytes,charsetName);

    (*env)->ReleaseStringUTFChars(env, str_, str);

    return stringTransFrom;
}

int compareTo(int* a,int* b){
    return (*a) - (*b);
}

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_MainActivity_sortArray(JNIEnv *env, jobject instance, jintArray array_) {
    jint *array = (*env)->GetIntArrayElements(env, array_, NULL);

    // TODO

    jsize size = (*env)->GetArrayLength(env,array_);

    qsort(array,size, sizeof(array[0]),compareTo);


    /**
     *
     * 释放引用，因为数组和对象在java都是引用，都会在堆中开辟一块内存空间，但我们使用完对象之后
     * 需要把引用释放掉，不然会耗内存，在一定程度上会找出内存溢出
     * JNI_ABORT Java数组不更新，但释放c/c++数组
     * JNI_COMMIT Java数组更新，不释放c/c++数组（函数执行完，还是会释放）
     *
     */

    (*env)->ReleaseIntArrayElements(env, array_, array, JNI_COMMIT);
}

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_MainActivity_localRef(JNIEnv *env, jobject instance) {

    // TODO

    jclass cls = (*env)->FindClass(env,"java/lang/String");

    jmethodID  mid = (*env)->GetMethodID(env,cls,"<init>","([BLjava/lang/String;)V");

    jobject  obj = (*env)->NewObject(env,cls,mid);

    jobject  localObj = (*env)->NewLocalRef(env,obj);

    (*env)->DeleteLocalRef(env,localObj);


}


jstring gobalString;

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_MainActivity_globalRef(JNIEnv *env, jobject instance, jstring string_) {
    const char *string = (*env)->GetStringUTFChars(env, string_, 0);

    // TODO
    gobalString = (*env)->NewWeakGlobalRef(env,string_);


    (*env)->ReleaseStringUTFChars(env, string_, string);
}


JNIEXPORT jstring JNICALL
Java_com_miaml_ndktest_MainActivity_getGlobalStr(JNIEnv *env, jobject instance) {

    // TODO
    return gobalString;
}

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_HelloNDK_fileEncrypt(JNIEnv *env, jclass type, jstring normalFilePath_,
                                            jstring encryptFilePath_, jstring password_) {
    const char *normalFilePath = (*env)->GetStringUTFChars(env, normalFilePath_, 0);
    const char *encryptFilePath = (*env)->GetStringUTFChars(env, encryptFilePath_, 0);
    const char *password = (*env)->GetStringUTFChars(env, password_, 0);

    // TODO


    FILE *frp = fopen(normalFilePath, "rb");
    FILE *fwp = fopen(encryptFilePath, "wb");

    if (frp == NULL || fwp == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG,"NDKActivity","文件打开失败");
        return;
    }

    int len = strlen(password);

    int buff;
    int index = 0;

    while ((buff = fgetc(frp)) != EOF){
        fputc(buff ^ *(password + index % len),fwp);
        index++;

    }

    fclose(fwp);
    fclose(frp);
    __android_log_print(ANDROID_LOG_DEBUG,"NDKActivity","加密成功");

    (*env)->ReleaseStringUTFChars(env, normalFilePath_, normalFilePath);
    (*env)->ReleaseStringUTFChars(env, encryptFilePath_, encryptFilePath);
    (*env)->ReleaseStringUTFChars(env, password_, password);
}

JNIEXPORT void JNICALL
Java_com_miaml_ndktest_HelloNDK_fileDecrypt(JNIEnv *env, jclass type, jstring encryptFilePath_,
                                            jstring decryptFilePath_, jstring password_) {
    const char *encryptFilePath = (*env)->GetStringUTFChars(env, encryptFilePath_, 0);
    const char *decryptFilePath = (*env)->GetStringUTFChars(env, decryptFilePath_, 0);
    const char *password = (*env)->GetStringUTFChars(env, password_, 0);

    // TODO

    FILE *frp = fopen(encryptFilePath, "rb");
    FILE *fwp = fopen(decryptFilePath, "wb");

    if (frp == NULL || fwp == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG,"NDKActivity","文件打开失败");
        return;
    }

    int len = strlen(password);

    int buff;
    int index = 0;

    while ((buff = fgetc(frp)) != EOF){
        fputc(buff ^ *(password + index % len),fwp);
        index++;
    }


    fclose(fwp);
    fclose(frp);
    __android_log_print(ANDROID_LOG_DEBUG,"NDKActivity","解密成功");


    (*env)->ReleaseStringUTFChars(env, encryptFilePath_, encryptFilePath);
    (*env)->ReleaseStringUTFChars(env, decryptFilePath_, decryptFilePath);
    (*env)->ReleaseStringUTFChars(env, password_, password);
}
int getFileSize(char* filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return -1;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);

    return size;
}
JNIEXPORT void JNICALL
Java_com_miaml_ndktest_HelloNDK_splitFile(JNIEnv *env, jclass type, jstring filePath_,
                                          jstring suffix_, jint splitFileNum) {
    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);
    const char *suffix = (*env)->GetStringUTFChars(env, suffix_, 0);
    const char* tag = "Java_com_miaml_ndktest_HelloNDK_splitFile";

    // TODO

    //保存分割文件路径
    char **split_file_path_list = (char **) malloc(sizeof(char *) * splitFileNum);
    FILE *frp = fopen(filePath, "rb");


    if (frp == NULL) {
        LOGE(tag, "%s", "filePath文件不存在");
        return;
    }
    int len = strlen(filePath);

    char tempFilePath[len + 10];

    strcpy(tempFilePath,filePath);
    strtok(tempFilePath,".");
    strcat(tempFilePath,"_%d");
    strcat(tempFilePath,suffix);


    __android_log_print(ANDROID_LOG_DEBUG,tag," --- tempFilePath = %s" , tempFilePath);


    for (int i = 0; i < splitFileNum; i++) {


        split_file_path_list[i] = (char *) malloc(sizeof(char) * 128);

        sprintf(split_file_path_list[i], tempFilePath, i);
        __android_log_print(ANDROID_LOG_DEBUG, tag, " --- 每个分割文件的路径 = %s", split_file_path_list[i]);

    }


    int file_size = getFileSize(filePath);


    if (file_size % splitFileNum == 0) { //整除情况


        int splitFileSize = file_size / splitFileNum; //每个分割文件的大小

        LOGE(tag, "每个文件大小 = %d ", splitFileSize);

        for (int i = 0; i < splitFileNum; i++) {

            FILE *fwp = fopen(split_file_path_list[i], "wb");

            if (fwp == NULL) {
                LOGE(tag, "%s", "split_file_path_list打开文件失败");
                return;
            }


            for (int j = 0; j < splitFileSize; j++) {

                fputc(fgetc(frp), fwp);
            }

            //关闭流
            fclose(fwp);

        }


    } else {

        int preSplitFileSize = file_size / (splitFileNum - 1);

        LOGE(tag, "splitFileNum-1 前的每个文件大小 = %d ", preSplitFileSize);

        int lastSplitFileSize = file_size % (splitFileNum-1);

        LOGE(tag, "最后个文件大小 = %d ", lastSplitFileSize);


        for (int i = 0; i < splitFileNum; i++) {


            FILE *fwp = fopen(split_file_path_list[i], "wb");

            if (fwp == NULL) {
                LOGE(tag, "%s", "split_file_path_list打开文件失败");
                return;
            }

            if (i == (splitFileNum - 1)) { //最后一个


                for (int j = 0; j < lastSplitFileSize; j++) {
                    fputc(fgetc(frp), fwp);
                }

            }else {

                for (int j = 0; j < preSplitFileSize; j++) {
                    fputc(fgetc(frp),fwp);
                }


            }

            //关闭流
            fclose(fwp);


        }

        fclose(frp);

        //释放动态内存

        for (int i = 0; i < splitFileNum; i++) {
            free(split_file_path_list[i]);
        }

        free(split_file_path_list);
    }




    (*env)->ReleaseStringUTFChars(env, filePath_, filePath);
    (*env)->ReleaseStringUTFChars(env, suffix_, suffix);
}