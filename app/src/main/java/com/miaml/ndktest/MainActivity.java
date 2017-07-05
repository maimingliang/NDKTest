package com.miaml.ndktest;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {



    public String name = "maiml";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    // Example of a call to a native method
    TextView tv = (TextView) findViewById(R.id.sample_text);
    tv.setText(stringFromJNI());

        Log.e("tag", "----- bf name = " + name);

        accessJaveStringField();

        Log.e("tag", "----- af name = " + name);

        Log.e("tag", "==== appkey = " + getAppkey());

        init();
    }

    private void init() {
        accessJavaMethod();
        long time = accessConstructorMethod();

        Log.e("Tag", "-----time = " + time);

        String transfrom = cTransfrom("拉阿拉");

        Log.e("tag", "----- transFrom = " + transfrom);

        int[] arr = {1,3,10,4,2,11,19};

        sortArray(arr);

        for(int i = 0 ;i< arr.length;i++){
            Log.e("tag"," i = "+ i +"  val = " + arr[i]);
        }


        globalRef("lala");
        String globalStr = getGlobalStr();

        Log.e("tag", "--- globalStr = " + globalStr);

        findViewById(R.id.btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,NDKActivity.class));
            }
        });

        findViewById(R.id.btn2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,UpdateApkActivity.class));
            }
        });

        findViewById(R.id.btn3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this,NewActivity.class));
            }
        });

    }


    private void print(int num){

        Log.e("tag", "-----> num = " + num);
//        return num;
    }





    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getAppkey();

    public native String printlog(String str);

    public native void accessJaveStringField();//c函数范围java的字段

    public native void accessJavaMethod();
    public native long accessConstructorMethod();

    public native String cTransfrom(String str);
    public native void sortArray(int[] array);

    public native void localRef();

    public native void globalRef(String string);

    public native String getGlobalStr();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
