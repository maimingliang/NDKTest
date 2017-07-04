package com.miaml.ndktest;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.File;

public class NDKActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText mEditText;
    private Button mButton;
    private Button mButton2;
    private Button mButton4;
    private Button mButton3;
    private String mNormalPath;
    private String mEncryptPath;
    private String mPassword;
    private Button mButton5;
    private String mDecryptPath;
    private String mSplitPath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ndk);

        mEditText = (EditText) findViewById(R.id.et);
        mButton = (Button) findViewById(R.id.btn1);
        mButton2 = (Button) findViewById(R.id.btn2);
        mButton3 = (Button) findViewById(R.id.btn3);
        mButton4 = (Button) findViewById(R.id.btn4);
        mButton5 = (Button) findViewById(R.id.btn5);



        init();
        setListener();
    }

    private void setListener() {
        mButton.setOnClickListener(this);
        mButton2.setOnClickListener(this);
        mButton3.setOnClickListener(this);
        mButton4.setOnClickListener(this);
        mButton5.setOnClickListener(this);
    }

    private void init() {

        mPassword = mEditText.getText().toString();

        if(TextUtils.isEmpty(mPassword)){
            mPassword = "xj";
        }

        mNormalPath = "/sdcard/DCIM/Camera/20170703_123916.jpg";
        mEncryptPath = "/sdcard/DCIM/Camera/20170604_181902.jpg";
        mDecryptPath = "/sdcard/DCIM/Camera/20170604_182410.jpg";
        mSplitPath = "/sdcard/DCIM/Camera/20170604_182410.jpg";



    }

    //android获取一个用于打开图片文件的intent
    public  Intent getImageFileIntent(String param ) {
        Intent intent = new Intent("android.intent.action.VIEW");
        intent.addCategory("android.intent.category.DEFAULT");
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        Uri uri = Uri.fromFile(new File(param ));
        intent.setDataAndType(uri, "image/*");
        return intent;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn1:
                HelloNDK.fileEncrypt(mNormalPath,mEncryptPath,mPassword);
                break;
            case R.id.btn2:
                HelloNDK.fileDecrypt(mEncryptPath,mDecryptPath,mPassword);
                break;
            case R.id.btn3:
                HelloNDK.splitFile(mSplitPath,".b",4);
                break;
            case R.id.btn4:
                break;
            case R.id.btn5:
                Intent imageFileIntent = getImageFileIntent(mEncryptPath);

                startActivity(imageFileIntent);
                break;
        }
    }
}
