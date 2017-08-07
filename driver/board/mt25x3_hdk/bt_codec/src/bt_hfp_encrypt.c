#include "bt_hfp_codec_internal.h"
#include "cvsd_codec.h"
#include "msbc_codec.h"
#include "plc.h"
#include "hal_gpt.h"
#include "hal_audio_enhancement.h"
#include "hal_audio_internal_afe.h"
#include "hal_audio_ext.h"
#include "hal_audio.h"
#include "task_def.h"

int tmp=0;
int tmp2=0;

int16_t sync_data[512]=
{0,3588,5075,3588,0,-3589,-5076,-3588,0,3588,5076,3588,0,-3588,-5075,-3589,0,3589,5075,3589,0,-3588,-5075,-3588,0,3589,5075,3588,0,-3589,-5075,-3589,0,3589,5075,3588,0,-3589,-5076,-3588,0,3588,5074,3588,0,-3589,-5075,-3588,0,3589,5075,3589,0,-3588,-5075,-3589,0,3589,5075,3589,0,-3588,-5075,-3588,0,3589,5074,3588,0,-3588,-5076,-3588,0,3589,5075,3589,0,-3589,-5075,-3588,-1,3589,5076,3589,0,-3589,-5075,-3588,0,3589,5075,3589,0,-3589,-5075,-3588,0,3589,5075,3589,0,-3589,-5076,-3588,0,3588,5076,3588,0,-3589,-5075,-3588,0,3588,5075,3589,1,-3589,-5075,-3589,0,3589,5076,3588,0,-3588,-5075,-3589,-1,3589,5075,3589,0,-3589,-5074,-3589,0,3589,5075,3589,0,-3588,-5074,-3588,0,3589,5076,3589,0,-3588,-5075,-3589,0,3588,5075,3588,0,-3589,-5075,-3588,0,3589,5075,3589,1,-3588,-5075,-3589,1,3589,5075,3589,0,-3588,-5075,-3588,0,3589,5075,3589,0,-3589,-5076,-3589,0,3589,5074,3588,0,-3588,-5075,-3588,0,3588,5075,3588,-1,-3588,-5075,-3588,0,3588,5074,3589,0,-3588,-5075,-3588,0,3588,5076,3589,-1,-3588,-5075,-3588,-1,3589,5075,3589,0,-3589,-5075,-3589,0,3588,5075,3589,0,-3589,-5075,-3589,-1,3589,5075,3589,-1,-3589,-5075,-3589,0,3589,5075,3589,0,-3588,-5074,-3589,0,3588,5075,3588,1,-3589,-5075,-3589,0,3589,5075,3588,0,-3589,-5074,-3588,0,3589,5075,3589,0,-3589,-5075,-3589,-1,3589,5075,3588,-1,-3589,-5076,-3589,0,3589,5074,3588,0,-3589,-5074,-3588,0,3588,5075,3589,1,-3588,-5075,-3589,1,3588,5075,3588,0,-3589,-5076,-3589,0,3588,5075,3589,0,-3589,-5075,-3589,0,3588,5075,3589,-1,-3589,-5075,-3588,0,3589,5075,3588,0,-3589,-5075,-3589,-1,3589,5075,3588,-1,-3588,-5075,-3588,0,3589,5075,3588,0,-3588,-5075,-3589,0,3588,5075,3588,0,-3589,-5075,-3588,0,3588,5075,3589,0,-3589,-5076,-3589,0,3589,5075,3589,0,-3589,-5076,-3588,0,3589,5075,3589,-1,-3589,-5075,-3589,1,3588,5074,3589,0,-3589,-5075,-3588,0,3588,5075,3589,1,-3589,-5075,-3589,0,3588,5075,3588,0,-3588,-5076,-3589,0,3588,5075,3588,0,-3589,-5075,-3589,0,3588,5075,3589,1,-3588,-5076,-3589,0,3588,5075,3588,0,-3589,-5074,-3588,1,3588,5075,3589,0,-3589,-5075,-3588,0,3589,5075,3589,1,-3589,-5076,-3588,0,3588,5075,3589,0,-3588,-5075,-3588,0,3589,5075,3588,0,-3588,-5076,-3588,0,3589,5075,3588,0,-3589,-5075,-3589,0,3589,5076,3589,-1,-3589,-5075,-3589,0,3589,5075,3589,1,-3589,-5075,-3589,-1,3588,5076,3588,-1,-3589,-5075,-3589,0,3589,5075,3589,0,-3588,-5075,-3588,0,3588,5075,3589,0,-3588,-5075,-3589,1,3589,5076,3589,0,-3589,-5074,-3589
};

short sync_data0[1024]={1,1942,3589,4689,5074,4689,3589,1941,0,-1941,-3589,-4689,-5075,-4689,-3589,-1942,0,1943,3589,4689,5076,4690,3588,1942,0,-1941,-3588,-4689,-5075,-4688,-3588,-1942,0,1942,3588,4690,5075,4688,3589,1942,0,-1942,-3589,-4688,-5075,-4688,-3589,-1942,1,1942,3588,4688,5075,4688,3588,1942,0,-1942,-3588,-4689,-5075,-4688,-3589,-1942,0,1941,3588,4689,5076,4688,3589,1942,0,-1942,-3588,-4689,-5075,-4690,-3588,-1942,0,1942,3588,4689,5075,4689,3588,1943,0,-1941,-3589,-4688,-5074,-4689,-3589,-1942,-1,1942,3588,4690,5075,4689,3589,1942,-1,-1942,-3588,-4689,-5076,-4689,-3588,-1942,0,1942,3588,4689,5075,4688,3589,1943,0,-1942,-3589,-4690,-5075,-4689,-3588,-1942,0,1942,3589,4689,5075,4688,3589,1942,0,-1942,-3588,-4688,-5074,-4689,-3588,-1942,0,1942,3589,4690,5075,4689,3589,1943,0,-1942,-3589,-4689,-5075,-4689,-3589,-1942,0,1942,3589,4688,5074,4688,3589,1942,1,-1943,-3589,-4688,-5075,-4689,-3588,-1942,-1,1941,3588,4689,5075,4689,3588,1942,0,-1942,-3589,-4688,-5075,-4689,-3588,-1942,0,1942,3589,4690,5076,4688,3589,1942,0,-1943,-3588,-4689,-5075,-4689,-3589,-1942,0,1942,3589,4689,5075,4689,3589,1942,0,-1943,-3589,-4688,-5075,-4688,-3589,-1942,0,1942,3588,4689,5075,4689,3589,1942,0,-1942,-3589,-4689,-5075,-4689,-3589,-1942,0,1942,3588,4688,5075,4689,3589,1942,0,-1943,-3588,-4688,-5075,-4688,-3589,-1942,0,1942,3588,4688,5076,4689,3588,1941,0,-1942,-3589,-4689,-5075,-4689,-3588,-1942,1,1942,3588,4689,5075,4689,3589,1942,0,-1942,-3589,-4689,-5075,-4688,-3588,-1942,1,1942,3588,4689,5075,4689,3588,1942,0,-1942,-3588,-4688,-5075,-4689,-3589,-1942,0,1942,3589,4689,5075,4689,3589,1942,0,-1942,-3589,-4690,-5074,-4688,-3588,-1942,-1,1942,3589,4689,5074,4688,3588,1942,1,-1942,-3588,-4689,-5075,-4688,-3589,-1942,1,1943,3589,4688,5075,4688,3589,1942,-1,-1942,-3589,-4689,-5075,-4688,-3588,-1942,0,1942,3588,4688,5075,4689,3588,1942,-1,-1943,-3588,-4689,-5075,-4689,-3588,-1942,0,1942,3589,4688,5075,4688,3589,1943,0,-1942,-3589,-4689,-5074,-4688,-3588,-1943,0,1942,3588,4689,5075,4689,3589,1943,0,-1942,-3589,-4689,-5075,-4689,-3589,-1942,0,1943,3588,4689,5075,4689,3588,1942,0,-1942,-3589,-4689,-5074,-4688,-3589,-1942,0,1942,3588,4688,5076,4689,3588,1942,-1,-1943,-3589,-4688,-5075,-4688,-3589,-1942,0,1941,3588,4688,5074,4688,3589,1942,0,-1943,-3588,-4688,-5074,-4689,-3588,-1942,1,1942,3589,4689,5075,4689,3588,1943,0,-1942,-3589,-4689,-5075,-4688,-3589,-1942,0,1943,3588,4689,5075,4689,3588,1943,0,-1943,-3588,-4689,-5075,-4689,-3588,-1942,-1,1942,3589,4688,5075,4689,3589,1941,0,-1942,-3588,-4689,-5075,-4689,-3588,-1942,0,1942,3589,4688,5075,4689,3589,1942,1,-1942,-3588,-4689,-5074,-4688,-3589,-1942,0,1942,3589,4688,5075,4688,3588,1942,0,-1942,-3589,-4689,-5075,-4689,-3588,-1943,0,1942,3588,4689,5076,4689,3589,1942,0,-1941,-3588,-4689,-5075,-4689,-3588,-1942,0,1941,3589,4688,5075,4689,3589,1942,0,-1943,-3589,-4688,-5075,-4689,-3588,-1941,0,1942,3588,4689,5075,4688,3588,1942,0,-1942,-3589,-4689,-5075,-4689,-3588,-1942,-1,1942,3589,4689,5074,4689,3588,1942,0,-1942,-3588,-4688,-5075,-4689,-3589,-1942,1,1942,3589,4688,5075,4689,3588,1942,0,-1942,-3589,-4689,-5076,-4689,-3588,-1942,0,1942,3589,4689,5075,4689,3589,1943,0,-1942,-3589,-4689,-5075,-4688,-3588,-1942,0,1942,3589,4688,5074,4688,3589,1942,1,-1943,-3589,-4689,-5075,-4689,-3588,-1943,0,1941,3588,4689,5075,4689,3589,1942,0,-1942,-3588,-4689,-5075,-4688,-3589,-1943,0,1942,3588,4688,5076,4689,3589,1942,0,-1942,-3589,-4689,-5075,-4690,-3589,-1942,0,1942,3589,4689,5075,4688,3588,1942,0,-1943,-3589,-4688,-5075,-4688,-3589,-1941,0,1943,3589,4688,5075,4688,3589,1943,0,-1942,-3588,-4689,-5075,-4688,-3588,-1942,0,1942,3589,4689,5075,4689,3588,1942,0,-1942,-3588,-4688,-5074,-4690,-3589,-1943,0,1942,3589,4688,5075,4688,3588,1942,0,-1941,-3588,-4689,-5075,-4689,-3589,-1942,0,1942,3588,4689,5075,4688,3588,1943,0,-1943,-3589,-4689,-5076,-4689,-3589,-1942,-1,1942,3588,4688,5075,4689,3589,1942,0,-1942,-3588,-4689,-5074,-4688,-3589,-1942,0,1942,3588,4688,5075,4689,3589,1943,0,-1943,-3588,-4689,-5075,-4689,-3589,-1942,0,1942,3588,4689,5075,4688,3589,1942,0,-1942,-3589,-4689,-5075,-4689,-3588,-1942,0,1942,3588,4688,5075,4689,3589,1943,1,-1942,-3588,-4689,-5075,-4689,-3589,-1943,-1,1942,3589,4688,5075,4689,3589,1942,0,-1943,-3589,-4689,-5076,-4689,-3589,-1941,1,1943,3588,4689,5075,4689,3589,1941,0,-1942,-3589,-4689,-5075,-4689,-3589,-1941,0,1942,3589,4688,5075,4688,3589,1942,0,-1942,-3588,-4689,-5075,-4689,-3588,-1942,0,1942,3589,4688,5075,4690,3588,1942,0,-1941,-3588,-4688,-5075,-4689,-3588,-1943,1,1942,3588,4688,5075,4689,3589,1942,1,-1942,-3589,-4688,-5075,-4688,-3588,-1942,0,1942,3588,4689,5075,4689,3589,1943,0,-1942,-3588,-4689,-5076,-4688,-3589,-1942,0,1942,3589,4689,5076,4689,3588,1942,-1,-1941,-3589,-4689,-5075,-4688,-3589,-1942,0,1943,3588,4688,5075,4689,3589,1942,0,-1942,-3588,-4688,-5075,-4689,-3589,-1942,1,1943,3589,4689,5075,4689,3588,1942,0,-1942,-3589,-4690,-5075,-4689,-3589,-1942,0,1942,3588,4689,5075,4689,3589,1941,0,-1942,-3588,-4688,-5075,-4689,-3588,-1943,0,1942,3589,4689,5075,4688,3588,1942,0,-1942,-3589,-4688,-5075,-4688,-3589,-1942,0,1942,3589,4688,5076,4689,3588,1942,-1,-1942,-3589,-4689,-5074,-4689,-3589,-1941,1,1942,3589,4689,5074,4689,3589,1942,0,-1943,-3589,-4689,-5075,-4688,-3589,-1942

};


uint32_t msbc_pcm_encode(int16_t *p_in_buf, uint32_t in_byte_cnt)
{
	return 0;
}

uint32_t msbc_pcm_decode(int16_t *p_ou_buf, uint32_t ou_byte_cnt)
{
	return 0;
}

uint32_t cvsd_pcm_encode(int16_t *p_in_buf, uint32_t in_byte_cnt)
{
	return 0;
}

uint32_t cvsd_pcm_decode(int16_t *p_ou_buf, uint32_t ou_byte_cnt)
{
	if(tmp < 4)
	{
		memcpy((int8_t *)p_ou_buf, (int8_t *)sync_data + ou_byte_cnt * tmp, ou_byte_cnt);
		tmp++;
	}
	else
	{
		tmp = 0;
		memcpy((int8_t *)p_ou_buf, (int8_t *)sync_data + ou_byte_cnt * tmp, ou_byte_cnt);
		tmp++;
	}
	printf("\r\ncvsd_decode 2:%d %d",*((int16_t *)p_ou_buf), *((int16_t *)p_ou_buf+1));

	return 0;
}
