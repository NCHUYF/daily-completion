#pragma once

#include "Date.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// Calendar
//
class Calendar : public Object2
{
public:
	enum FIELD
	{
		//ERA = 0,
		YEAR = 1,
		//MONTH = 2,
		//WEEK_OF_YEAR = 3,
		//WEEK_OF_MONTH = 4,
		//DATE = 5,
		//DAY_OF_MONTH = 5,
		DAY_OF_YEAR = 6,
		DAY_OF_WEEK = 7,
		//DAY_OF_WEEK_IN_MONTH = 8,
		//AM_PM = 9,
		//HOUR = 10,
		HOUR_OF_DAY = 11,
		MINUTE = 12,
		SECOND = 13,
		//MILLISECOND = 14,
		//ZONE_OFFSET = 15,
	};

	Calendar();

	static std::shared_ptr<Calendar> getInstance();

	void setTime(DatePtr date);

	DatePtr getTime();

	int getFirstDayOfWeek();

	int get(FIELD field);

	void set(FIELD field, int value);

	/**
	* �õ�ָ���ֶε����ֵ
	* @param field	Ŀǰֻ֧�� DAY_OF_YEAR
	*/
	int getActualMaximum(FIELD field);

	/**
	* add()���������߼��ϸı������ֶΣ�ʹ�����ȷ��
	* @param field	Ŀǰֻ֧�� DAY_OF_YEAR
	*/
	void add(FIELD field, int value);

	/**
	* roll()����ֻ�����Ӧ���ֶν��д����������ܵĶ������ֶ�Ҳ�����߼��ϵĸı䡣
	* @param field	Ŀǰֻ֧�� YEAR
	*/
	void roll(FIELD field, int value);

	virtual CString toString();

protected:
#ifdef _DEBUG
	CString _textDate;
#endif

protected:
	time_t	_time;	// ��ǰ���õ�ʱ��
};

typedef std::shared_ptr<Calendar> CalendarPtr;

/****************************************************************************************
Java ����ָ�����ڼ��������ܵ���һ������
1.
5.      private static void convertWeekByDate(Date time) {
6.
7.          SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd"); //����ʱ���ʽ
8.          Calendar cal = Calendar.getInstance();
9.          cal.setTime(time);
10.         //�ж�Ҫ����������Ƿ������գ���������һ����������ģ����������⣬���㵽��һ��ȥ��
11.         int dayWeek = cal.get(Calendar.DAY_OF_WEEK);//��õ�ǰ������һ�����ڵĵڼ���
12.         if(1 == dayWeek) {
13.             cal.add(Calendar.DAY_OF_MONTH, -1);
14.         }
15.         System.out.println("Ҫ��������Ϊ:"+sdf.format(cal.getTime())); //���Ҫ��������
16.         cal.setFirstDayOfWeek(Calendar.MONDAY);//����һ�����ڵĵ�һ�죬���й���ϰ��һ�����ڵĵ�һ��������һ
17.         int day = cal.get(Calendar.DAY_OF_WEEK);//��õ�ǰ������һ�����ڵĵڼ���
18.         cal.add(Calendar.DATE, cal.getFirstDayOfWeek()-day);//���������Ĺ��򣬸���ǰ���ڼ�ȥ���ڼ���һ�����ڵ�һ��Ĳ�ֵ
19.         String imptimeBegin = sdf.format(cal.getTime());
20.         System.out.println("����������һ�����ڣ�"+imptimeBegin);
21.         cal.add(Calendar.DATE, 6);
22.         String imptimeEnd = sdf.format(cal.getTime());
23.         System.out.println("�����������յ����ڣ�"+imptimeEnd);
24.
25.     }


Calendar��add()��roll()�������÷�
һ��ȡĳ��ʱ���������ʱ�̡�����1984��7��7��15:23:05�������ʱ�̼�Ϊ1984-07-07 16:00:00��
ʵ�����£�
Calendar calendar = Calendar.getInstance();
calendar.add(Calendar.HOUR_OF_DAY, 1);//Сʱ�ϼ�1
calendar.set(Calendar.MINUTE, 0);//������Ϊ0
calendar.set(Calendar.SECOND, 0);//������Ϊ0

����ȡĳ������֮ǰ��ĳ���¡�����Ҫȡ2002��1��12��֮ǰ1���µ�ʱ�䣬Ӧ����2001��12��12�ա�
Calendar calendar = Calendar.getInstance();
calendar.set(2002, 0, 12);//����2002��1��12��
calendar.add(Calendar.MONTH, -1);//�����ͽ��������ó���2001��12��12�ա�
System.out.println(calendar.getTime().toString());

����������������roll()��ʵ�֡������´��룺
Calendar calendar = Calendar.getInstance();
calendar.set(2002, 0, 12);//����2002��1��12��
calendar.roll(Calendar.MONTH, -1);//�����ͽ��������ó���2002��12��12�ա�
System.out.println(calendar.getTime().toString());

���ۣ�roll()��������ֻ�����Ӧ���ֶν��д����������ܵĶ������ֶ�Ҳ�����߼��ϵĸı䡣
����add()���������߼��ϸı������ֶΣ�ʹ�����ȷ��

ע��Calendar�е�Month�Ǵ�0-11�ģ�0����1�£�11����12�¡�

****************************************************************************************/