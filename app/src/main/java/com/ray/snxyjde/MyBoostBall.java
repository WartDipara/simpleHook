package com.ray.snxyjde;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class MyBoostBall extends View {

    private float mRadius;
    private Paint mPaintCircle;

    private float lastX, lastY, downX, downY;
    private static final int DRAG_THRESHOLD = 10;
    private boolean isDragging = false;

    public MyBoostBall(Context context) {
        this(context, null);
    }

    public MyBoostBall(Context context, @Nullable AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public MyBoostBall(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mPaintCircle = new Paint(Paint.ANTI_ALIAS_FLAG);
        mPaintCircle.setColor(0xFF12cdb0);
        setClickable(true);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        mRadius = Math.min(w, h) * 0.4f;
    }

    @Override
    protected void onDraw(@NonNull Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawCircle(getWidth()/2f, getHeight()/2f, mRadius, mPaintCircle);
    }

    @Override
    public boolean performClick() {
        super.performClick();
        Context context = getContext();
        if(context instanceof MainActivity){
            //todo show dialog
            new MyToolsDialog((MainActivity)context).show();
        }else{
            //todo fallback dialog
            new MyToolsDialog(context).show();
        }
        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        float cx = getWidth() / 2f;
        float cy = getHeight() / 2f;
        float x = event.getX();
        float y = event.getY();
        switch(event.getAction()){
            case MotionEvent.ACTION_DOWN:{
                float dist = (float)Math.hypot(x - cx, y - cy);
                if(dist > mRadius){
                    isDragging = false;
                    return false;
                }
                downX = lastX = event.getRawX();
                downY = lastY = event.getRawY();
                isDragging = true;
                return true;
            }
            case MotionEvent.ACTION_MOVE:{
                if(isDragging){
                    float dx = event.getRawX() - lastX;
                    float dy = event.getRawY() - lastY;
                    float newX = getX() + dx;
                    float newY = getY() + dy;
                    int parentWidth = ((View)getParent()).getWidth();
                    int parentHeight = ((View)getParent()).getHeight();
                    newX = Math.max(0, Math.min(newX, parentWidth - getWidth()));
                    newY = Math.max(0, Math.min(newY, parentHeight - getHeight()));
                    setX(newX);
                    setY(newY);
                    lastX = event.getRawX();
                    lastY = event.getRawY();
                }
                return isDragging;
            }
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:{
                if(isDragging){
                    isDragging = false;
                    float totalDx = Math.abs(event.getRawX()-downX);
                    float totalDy = Math.abs(event.getRawY()-downY);
                    if(totalDx < DRAG_THRESHOLD && totalDy < DRAG_THRESHOLD) {
                        performClick();
                    }
                    return true;
                }
                return false;
            }
        }
        return super.onTouchEvent(event);
    }
}
