package com.miaml.ndktest;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.google.gson.Gson;
import com.zhy.http.okhttp.OkHttpUtils;
import com.zhy.http.okhttp.callback.StringCallback;

import java.io.File;

import okhttp3.Call;

public class UpdateApkActivity extends AppCompatActivity {


    public static final String PREVIEW ="http://192.168.0.232:8089/";//图片路径

    private static final String TAG = "UpdateApkActivity";
    private ProgressDialog mProgressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_update_apk);
        mProgressBar = new ProgressDialog(this);
        mProgressBar.setMax(100);
        mProgressBar.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
        mProgressBar.setCanceledOnTouchOutside(false);

        check();
//        update();
    }

    private void check() {

        OkHttpUtils.post().url("http://192.168.0.232:8081/elk-tourist-develop/appUpdate/check")
                .addParams("appType","0")
                .addParams("versionNumber","1.3.0")
                .build().execute(new StringCallback() {
            @Override
            public void onError(Call call, Exception e, int id) {
                Log.e("tag", "----error = " + e.getMessage());
            }

            @Override
            public void onResponse(String response, int id) {
                Log.e("tag", " ---- res = " + response);

                Gson gson = new Gson();
                UpdateBean updateBean = gson.fromJson(response, UpdateBean.class);

                if (updateBean == null) {
                    return;
                }

                if (updateBean.getData() == null) {
                    return;
                }

                if (updateBean.getData().getFileInfoExt() == null) {
                    return;
                }

                String url = PREVIEW + updateBean.getData().getFileInfoExt().getFullPath();

                update(url);

            }
        });
    }

    private void update(String url) {

        mProgressBar.show();
        DownloadUtil.get().download(url, "/sdcard/", "patch.apk", new DownloadUtil.OnDownloadListener() {
            @Override
            public void onDownloadSuccess(File file) {
                if(file == null){
                    Log.e("tag", "---下载失败");
                    return;
                }
                Log.e("tag", "------> file path = " + file.getAbsolutePath());
                mProgressBar.dismiss();
                //获取当前应用的apk文件/data/app/app
                String oldFile = ApkUtils.getSourceApkPath(UpdateApkActivity.this, getPackageName());
                //2.合并得到最新版本的APK文件
                String newApkPath = "/sdcard/meger.apk";

                String patchFileAbsolutePath = file.getAbsolutePath();
                Log.e(TAG, "oldfile:"+oldFile);
                Log.e(TAG, "newfile:"+newApkPath);
                Log.e(TAG, "patchfile:"+patchFileAbsolutePath);
                BspatchNDK.bspatch(oldFile, newApkPath, patchFileAbsolutePath);



                ApkUtils.installApk(UpdateApkActivity.this,newApkPath);

            }

            @Override
            public void onDownloading(int progress) {
                Log.e("tag", "---progress = " + progress);
                mProgressBar.setProgress(progress);
            }

            @Override
            public void onDownloadFailed() {
                Log.e("tag", "---下载失败");
                mProgressBar.dismiss();
            }
        });
    }


}
