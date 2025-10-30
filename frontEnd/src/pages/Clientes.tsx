export default function Clientes() {
  const clientes = [
    { nome: "Lucas Silva", email: "lucas@gmail.com", contato: "11 99999-1234", membro: "Sim" },
    { nome: "Mariana Souza", email: "mariana@gmail.com", contato: "11 98888-4321", membro: "Não" },
  ];

  return (
    <div className="bg-white rounded-2xl shadow-md p-6">
      <div className="flex justify-between items-center mb-6">
        <h2 className="text-xl font-semibold text-gray-800">Clientes</h2>
        <button className="bg-blue-500 hover:bg-blue-600 text-white font-medium px-4 py-2 rounded-lg">
          + Novo Cliente
        </button>
      </div>

      <table className="w-full border-collapse">
        <thead>
          <tr className="bg-gray-200 text-gray-700">
            <th className="p-3 text-left">Nome</th>
            <th className="p-3 text-left">Email</th>
            <th className="p-3 text-left">Contato</th>
            <th className="p-3 text-left">Membro do Clube</th>
            <th className="p-3 text-center">Ações</th>
          </tr>
        </thead>
        <tbody>
          {clientes.map((c, i) => (
            <tr key={i} className="border-b hover:bg-gray-50">
              <td className="p-3">{c.nome}</td>
              <td className="p-3">{c.email}</td>
              <td className="p-3">{c.contato}</td>
              <td className="p-3">{c.membro}</td>
              <td className="p-3 text-center space-x-2">
                <button className="bg-yellow-400 hover:bg-yellow-500 text-white px-3 py-1 rounded-md">Editar</button>
                <button className="bg-red-500 hover:bg-red-600 text-white px-3 py-1 rounded-md">Excluir</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
