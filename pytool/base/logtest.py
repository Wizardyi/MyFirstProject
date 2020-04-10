#encoding=utf-8
import logging
logging.basicConfig(level=logging.DEBUG,
                    filename='new.log',
                    filemode='a',
                    format=
                    '%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s'
                    )
logging.debug(u'debug 信息')
logging.info(u'info 信息')
logging.warning(u'warning 信息')
logging.error(u'error 信息')
logging.critical(u'critial 信息')