package org.cocos2dx.cpp;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.poxiao.findthings.R;
import com.tallbigup.android.cloud.LayoutUtil;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.android.cloud.recommend.AsyncImageLoader;
import com.tallbigup.android.cloud.recommend.RecommendCallback;
import com.tallbigup.android.cloud.recommend.AsyncImageLoader.ImageCallback;

import android.app.Activity;
import android.app.Dialog;
import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.TextView;

public class QuitGameDialog extends Dialog {

	private Activity activity;

	private GridView gridView;
	private TextView noOtherGameTip;
	private TextView quit_text;
	private Button confirm;
	private Button quit;

	private List<String[]> recommends = new ArrayList<String[]>();

	private CrossRecommendAdapter adapter;

	public QuitGameDialog(Context context) {
		super(context, LayoutUtil.getMoreGamedialogStyleResId());
		this.activity = (Activity) context;
	}

	@Override
	public void onCreate(Bundle bundle) {
		super.onCreate(bundle);
		setContentView(R.layout.dialog_quit_game);
		adapter = new CrossRecommendAdapter(null);
		Log.e("CS","NetWorkService.isShowMoreGame="+NetWorkService.isMoreGame);
		if (NetWorkService.isMoreGame) {
			initView();
			initDatas();
		} else {
			initView();
			setNoRecommend();
		}
	}

	private void setNoRecommend() {
		quit_text.setVisibility(View.VISIBLE);
	}

	private void initView() {
		confirm = (Button) findViewById(R.id.quit_confirm);
		quit = (Button) findViewById(R.id.quit_cancel);
		quit_text = (TextView) findViewById(R.id.quit_text);
		confirm.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View arg0) {
				dismiss();
			}
		});
		quit.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				GameApplication.getInstance().fullExitApplication();
			}
		});
		noOtherGameTip = (TextView) findViewById(LayoutUtil
				.getMoreGameNoDataTipResId());
		gridView = (GridView) findViewById(LayoutUtil
				.getMoreGameGridViewResId());
		gridView.setSelector(new ColorDrawable(Color.TRANSPARENT));
		gridView.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				String[] info = (String[]) parent.getItemAtPosition(position);
				doStartNewGame(info[2], info[3], info[4]);
			}
		});
		gridView.setAdapter(adapter);
	}

	/**
	 * 
	 * @param param
	 * @param url
	 */
	private void doStartNewGame(String pack, String param, String url) {
		try {
			Intent intent = new Intent(Intent.ACTION_MAIN);
			intent.addCategory(Intent.CATEGORY_LAUNCHER);
			ComponentName cn = new ComponentName(pack, param);
			intent.setComponent(cn);
			activity.startActivity(intent);
		} catch (ActivityNotFoundException anf) {
			Intent intent = new Intent();
			intent.setAction("android.intent.action.VIEW");
			Uri content_url = Uri.parse(url);
			intent.setData(content_url);
			activity.startActivity(intent);
		}
	}

	protected void initDatas() {
		if (this.recommends != null && this.recommends.size() > 0) {
			adapter.updateDatas(recommends);
			return;
		}
		TbuCloud.getRecommendList(getChannelId(activity),
				new RecommendCallback() {

					@Override
					public void result(boolean success,
							Map<Integer, String[]> recommendList) {
						if (success && recommendList != null
								&& recommendList.size() > 0) {
							for (int i = 0; i < recommendList.size(); i++) {
								recommends.add(recommendList.get(i));
							}
							adapter.updateDatas(recommends);
						} else {
							getOtherGameList();
						}
					}
				});
	}

	class CrossRecommendAdapter extends BaseAdapter {

		private List<String[]> recommendRoomInfos = new ArrayList<String[]>();

		public CrossRecommendAdapter(List<String[]> recommendRoomInfos) {
			if (recommendRoomInfos != null && recommendRoomInfos.size() > 0) {
				this.recommendRoomInfos = recommendRoomInfos;
			}
		}

		@Override
		public int getCount() {
			if (recommendRoomInfos.size() > 0) {
				return recommendRoomInfos.size();
			}
			return 0;
		}

		@Override
		public Object getItem(int position) {
			return recommendRoomInfos.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			ViewHolder holder = null;
			holder = new ViewHolder();
			LayoutInflater inflater = (LayoutInflater) activity
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(
					LayoutUtil.getMoreGameViewItemLayoutResId(), null);
			holder.gameIcon = (ImageView) convertView.findViewById(LayoutUtil
					.getMoreGameViewItemGameIconResId());
			holder.gameName = (TextView) convertView.findViewById(LayoutUtil
					.getMoreGameViewItemGameNameResId());
			convertView.setTag(holder);
			String[] info = recommendRoomInfos.get(position);

			if (info != null) {
				if (info[0].length() > 0 && !info.equals("")) {
					holder.loadImage(info[0]);
				}
				if (info[1].length() > 0 && !info.equals("")) {
					holder.gameName.setText(info[1]);
				}
			}
			return convertView;
		}

		public void updateDatas(List<String[]> crossRecommendList) {
			if (null != crossRecommendList && crossRecommendList.size() > 0) {
				this.recommendRoomInfos.clear();
				this.recommendRoomInfos.addAll(crossRecommendList);
				notifyDataSetChanged();
			}
		}
	}

	class ViewHolder {
		ImageView gameIcon;
		TextView gameName;

		boolean mIsLoadImage = false;
		AsyncImageLoader mAsyncImageLoader = new AsyncImageLoader();

		public void loadImage(final String iconUrl) {
			if (!mIsLoadImage && (null != gameIcon)) {
				mIsLoadImage = true;
				Drawable drawable = mAsyncImageLoader.loadDrawable(iconUrl,
						new ImageCallback() {

							@Override
							public void imageLoaded(Bitmap bitMap,
									String imageUrl) {

							}

							@Override
							public void imageLoaded(Drawable imageDrawable,
									String imageUrl) {
								gameIcon.setImageDrawable(imageDrawable);
							}
						});
				if (null != drawable) {
					gameIcon.setImageDrawable(drawable);
				}
			}
		}
	}

	private void getOtherGameList() {
		noOtherGameTip.setVisibility(View.VISIBLE);
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
	}

	private String getChannelId(Context context) {
		ApplicationInfo appInfo;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);
			return appInfo.metaData.getString("Channel ID");
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			return "unknown";
		}
	}
}
