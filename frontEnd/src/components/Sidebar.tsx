import logo from '../assets/SC.png'
import calIcon from '../assets/calendario.png'
import funcIcon from '../assets/funcionarios.png'
import clientIcon from '../assets/cliente.png'

import type { ReactNode } from 'react'

type Props = {
    activePath?: string
    onNavigate?: (path: string) => void
}

interface NavItem {
  key: string
  path: string
  label: string
  icon: ReactNode
}

export default function Sidebar({ activePath, onNavigate }: Props) {
    const items: NavItem[] = [
        {
            key: 'agendamentos',
            path: '/agendamentos',
            label: 'Agendamentos',
            icon: <img src={calIcon} alt="agendamentos" className="w-5 h-5 object-contain nav-icon" />,
        },
        {
            key: 'funcionarios',
            path: '/funcionarios',
            label: 'Funcionários',
            icon: <img src={funcIcon} alt="funcionarios" className="w-6 h-6 object-contain nav-icon" />,
        },
        {
            key: 'clientes',
            path: '/clientes',
            label: 'Clientes',
            icon: <img src={clientIcon} alt="clientes" className="w-5 h-5 object-contain nav-icon" />,
        },
        {
            key: 'servicos',
            path: '/servicos',
            label: 'Serviços',
            icon: null,
        },
    ]

    const navigate = (path: string) => {
        // atualiza a URL sem recarregar e notifica o pai
        window.history.pushState({}, '', path)
        onNavigate?.(path)

    }

    return (
        <aside className="w-64 min-h-screen border-r border-gray-200 bg-white flex flex-col">
            <div className="flex items-center text-left py-6 px-4 gap-3">
                <img src={logo} alt="SC" className="w-15 h-15 object-contain" />
                <div>
                    <h1 className="text-lg text-black">CinBarber</h1>
                    <p className="text-sm text-gray-500">Gerenciamento</p>
                </div>
            </div>

            <div className="border-b border-gray-200 mb-6"></div>

            <nav className="flex py-2 px-5 flex-col gap-3">
                {items.map((it) => {
                    const isActive = it.path === activePath
                    return (
                        <a
                            key={it.path}
                            href={it.path}
                            onClick={(e) => {
                                e.preventDefault()
                                navigate(it.path)
                            }}
                            className={
                                'flex items-center gap-3 px-4 py-3 rounded-lg transition-colors text-sm font-medium ' +
                                (isActive ? 'nav-item-active bg-red-700 text-white' : 'text-gray-700')
                            }
                        >
                            <span className="flex items-center justify-center w-6 h-6">{it.icon}</span>
                            <span>{it.label}</span>
                        </a>
                    )
                })}

        
            
            </nav>

            <div className="border-t border-gray-200 mt-auto py-6">
                <div className="px-3">
                    <div className="bg-gray-50 border border-gray-100 rounded-lg p-3 shadow-sm w-full">
                        <h1 className="text-sm font-medium text-gray-800">Painel do Gerente</h1>
                        <p className="text-xs text-gray-400">v1.0.0</p>
                    </div>

                </div>
            </div>
            
        </aside>
    )
}

